import { useState } from "react";
import { useApiWithLoading, Client } from "../api";
import { Link } from "react-router-dom";


export default function MainPage() {
    let [id, setId] = useState(1)
    let client = useApiWithLoading<Client>((api) => api.get("/clients/" + id), [id])

    return (
        <div>
            <h1>
                MainPage
            </h1>
            {
                client.loading ? (
                    <p>"Loading..."</p>
                ) : (
                    <p>{client.value?.name}</p>
                )
            }
            <Link to="/upload-trip">Upload Trip</Link>
        </div>
    );
}