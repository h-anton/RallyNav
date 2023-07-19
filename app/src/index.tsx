import React, { useState } from 'react';
import ReactDOM from 'react-dom/client';
import './index.css';
import * as serviceWorkerRegistration from './serviceWorkerRegistration';
import reportWebVitals from './reportWebVitals';
import { Outlet, RouterProvider, createBrowserRouter } from 'react-router-dom';
import ErrorPage from './pages/ErrorPage';
import MainPage from './pages/MainPage';
import LoginPage from './pages/LoginPage';
import { getCookies } from './api';
import UploadTripPage from './pages/UploadTripPage';

const root = ReactDOM.createRoot(
  document.getElementById('root') as HTMLElement
);

const router = createBrowserRouter([
  {
    path: "/",
    element: <App/>,
    errorElement: <ErrorPage/>,
    children: [
      {
        path: "",
        element: <MainPage/>
      },
      {
        path: "upload-trip",
        element: <UploadTripPage/>
      }
    ]
  }
]);


function App() {
  const [loggedIn, setLoggedIn] = useState<boolean>(
    getCookies().SITE_SESSION !== undefined
  );
  
  if (!loggedIn) {
    return (<LoginPage setLoggedIn={setLoggedIn}/>)
  }

  return (<Outlet/>);
}

root.render(
  <React.StrictMode>
    <RouterProvider router={router} />
  </React.StrictMode>
);

// If you want your app to work offline and load faster, you can change
// unregister() to register() below. Note this comes with some pitfalls.
// Learn more about service workers: https://cra.link/PWA
serviceWorkerRegistration.unregister();

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();
