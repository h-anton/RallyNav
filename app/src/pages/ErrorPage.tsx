import { useRouteError } from "react-router-dom";
import { AlertTitle, Typography, Alert, Grid } from "@mui/material";

export default function ErrorPage() {
  const error: any = useRouteError();
  console.error(error);

  return (
    <Grid container justifyContent="center" alignItems="center" sx={{height: '100%'}}>
        <Alert severity="error">
            <AlertTitle>Oops!</AlertTitle>
            <Typography variant="subtitle1" component="p">
                Sorry, an unexpected error has occurred.
            </Typography>
            <br/>
            <Typography variant="subtitle2" component="p">
                {error.statusText || error.message}
            </Typography>
        </Alert>
    </Grid>
  );
}