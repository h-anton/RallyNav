
import _axios, { AxiosRequestConfig } from "axios"
import { AxiosInstance } from "axios"
import { DependencyList, useEffect, useState } from "react"

const axios: AxiosInstance = _axios.create({
    withCredentials: true,
    baseURL: window.location.origin.includes("localhost") ? "http://localhost:3000" : (window.location.origin + "/api"),
    headers: {
        'Content-Type': 'application/json'
    }
})

// defining a custom error handler for all APIs
const errorHandler = (error: any) => {
    console.error(error)
    return Promise.reject(error)
}

export interface LoginInput {
    token: string
}

export interface ApiCall<T> {
    get value(): T | undefined,
    get loading(): boolean,
}

export class ApiInstance {
    constructor() {
        axios.interceptors.response.use(undefined, (error) => { return errorHandler(error) })
    }

    async token_login(data: LoginInput): Promise<string> {
        return (await axios.post('/tlogin', data)).data
    }

    get<T>(url: string, params?: AxiosRequestConfig): Promise<T> {
        return axios.get<T>(url, params)
            .then((response) => response.data)
    }

    post<C, T>(url: string, data: C, params?: AxiosRequestConfig): Promise<T> {
        return axios.post<T>(url, data, params)
            .then((response) => response.data)
    }

    put<C, T>(url: string, data: C, params?: AxiosRequestConfig): Promise<T> {
        return axios.put<T>(url, data, params)
            .then((response) => response.data)
    }

    delete<T>(url: string, params?: AxiosRequestConfig): Promise<T> {
        return axios.delete<T>(url, params)
            .then((response) => response.data)
    }
}

export function getCookies() {
    if (document.cookie === "") return {};

    var pairs = document.cookie.split(";");
    var cookies: any = {};
    for (var i = 0; i < pairs.length; i++) {
        var pair = pairs[i].split("=");
        cookies[(pair[0] + '').trim()] = unescape(pair.slice(1).join('='));
    }

    return cookies;
}

const api = new ApiInstance()

export function callApi<T>(use: (instance: ApiInstance) => Promise<T>): () => Promise<T> {
    return async () => await use(api)
}

export function useApiWithLoading<T>(use: (instance: ApiInstance) => Promise<T>, deps?: DependencyList): ApiCall<T> {
    let [loading, setLoading] = useState(true)
    let [value, setValue] = useState<T>()

    class ApiCallInstance {
        get value(): T | undefined { return value }

        get loading(): boolean { return loading }
    }

    useEffect(() => {
        use(api).then((result) => {
            setLoading(false)
            setValue(result)
        })

        return () => {}
// eslint-disable-next-line react-hooks/exhaustive-deps
    }, deps)

    return new ApiCallInstance()
}

export interface Client {
    id: number,
    name: string,
    email: string,
    phone: string,
    address: string,
    city: string,
    country: string,
    postalCode: string,
}