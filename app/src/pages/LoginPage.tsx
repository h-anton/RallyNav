import { Alert, Button, Card, CardActions, CardContent, Grid, TextField, Typography } from "@mui/material";
import { useApi } from "../api";
import { useState } from "react";

export default function LoginPage(props: {setLoggedIn: (loggedIn: boolean) => void}) {
    const [token, setToken] = useState("");
    const [error, setError] = useState("");

    let onLogin = useApi(async (api) => {
        try {
            await api.token_login({ token })
            props.setLoggedIn(true)
        } catch (e: any) {
            setError(e.response?.data ?? "Unknown error please try to contact support")
        }
    })

    return (
        <Grid container justifyContent="center" alignItems="center" sx={{height: '100%'}}>
            <Card>
                <CardContent>
                    <Typography variant="h5" component="h1" sx={{textAlign: 'center'}} mb={1}>Login</Typography>
                    {error ? <Alert severity="error">{error}</Alert> : undefined}
                    <TextField label="Token" variant="standard" onChange={(e) => setToken(e.target.value)}/>
                </CardContent>
                <CardActions>
                    <Grid container justifyContent="center" alignItems="center">
                        <Button variant="contained" onClick={onLogin}>Login</Button>
                    </Grid>
                </CardActions>
            </Card>
        </Grid>
    );
  }