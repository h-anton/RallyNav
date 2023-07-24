import { ChangeEvent, useState } from "react";
import { callApi } from "../api";
import { Alert, Button, Card, CardActions, CardContent, Grid, Typography } from "@mui/material";
import { useNavigate } from "react-router-dom";

export default function UploadTripPage() {
    const navigate = useNavigate();
    const [file, setFile] = useState<File>();
    const [error, setError] = useState<string>();
    const [success, setSuccess] = useState<boolean>(false);

    const handleFileChange = (e: ChangeEvent<HTMLInputElement>) => {
        if (e.target.files) {
            setFile(e.target.files[0]);
        }
    };

    const uploadFile = callApi(async (api) => {
        try {
            await api.post("/trips", file, {
                headers: {
                    "Content-Type": "application/gpx+xml"
                }
            })
        } catch (e: any) {
            let response = e.response?.data
            if (!response)
                response = e.message

            if (!response)
                response = "Unknown error please try to contact support"

            setError(response)
            return
        }

        setError(undefined)
        setSuccess(true)
    })

    const handleUploadClick = () => {
        if (!file) {
            setError("Please select a file to upload")
        }

        uploadFile()
    }

    return (
        <Grid container justifyContent="center" alignItems="center" sx={{ height: '100%' }}>
            {
                success ? (
                    <Card sx={{width: "40%"}}>
                        <CardContent>
                            <Typography alignContent="center">Upload suceeded</Typography>
                        </CardContent>
                        <CardActions>
                            <Grid container>
                                <Grid item xs={6} p={1}>
                                    <Button variant="contained" sx={{width: "100%"}} onClick={() => navigate(-1)}>
                                        Go Back
                                    </Button>
                                </Grid>
                                <Grid item xs={6} p={1}>
                                    <Button variant="contained" sx={{width: "100%"}} onClick={() => {
                                        setSuccess(false)
                                        setFile(undefined)
                                    }}>Upload another trip</Button>
                                </Grid>
                            </Grid>
                        </CardActions>
                    </Card>
                ) : (
                    <Card>
                        <CardContent>
                            {error ? <Alert severity="error">{error}</Alert> : undefined}
                            <input type="file" onChange={handleFileChange} />
                            <div>{file && `${file.name} - ${file.type}`}</div>
                        </CardContent>
                        <CardActions>
                            <Grid container justifyContent="center" alignItems="center">
                                <Grid item xs={4} p={1}>
                                    <Button variant="contained" sx={{width: "100%"}} onClick={() => navigate(-1)}>Back</Button>
                                </Grid>
                                <Grid item xs={8} p={1}>
                                    <Button variant="contained" sx={{width: "100%"}} onClick={handleUploadClick}>Upload</Button>
                                </Grid>
                            </Grid>
                        </CardActions>
                    </Card>
                )
            }
        </Grid>
    );
}