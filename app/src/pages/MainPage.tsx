import { useState } from "react";
import { useApiWithLoading, Client } from "../api";
import { useNavigate } from "react-router-dom";
import { AppBar, Box, Drawer, Divider, ListItemText, Typography, IconButton, Toolbar, List, ListItem, ListItemButton, ListItemIcon } from "@mui/material";
import MenuIcon from '@mui/icons-material/Menu';
import InboxIcon from '@mui/icons-material/MoveToInbox';
import ChevronLeftIcon from '@mui/icons-material/ChevronLeft';
import ChevronRightIcon from '@mui/icons-material/ChevronRight';
import StreetMap from "../components/StreetMap";

const leftDrawerWidth = 180
const rightDrawerWidth = 240

export default function MainPage() {
    //let [id, setId] = useState(1)
    //let client = useApiWithLoading<Client>((api) => api.get("/clients/" + id), [id])

    const navigate = useNavigate();
    const [leftDrawer, setLeftDrawer] = useState(true)
    const [rightDrawer, setRightDrawer] = useState(false)

    return (
        <Box sx={{height: "100%", display: "flex"}}>
            <AppBar position="fixed" sx={{ zIndex: (theme) => theme.zIndex.drawer + 1 }}>
                <Toolbar>
                    <IconButton
                        color="inherit"
                        aria-label="open left drawer"
                        edge="end"
                        onClick={() => setLeftDrawer(true)}
                        sx={{ mr: 2, ...(leftDrawer && { display: 'none' }) }}
                    >
                        <MenuIcon/>
                    </IconButton>

                    <Typography variant="h6" noWrap textAlign="center" component="div" sx={{flexGrow: 1}}>
                        Overview
                    </Typography>

                    <IconButton
                        color="inherit"
                        aria-label="open right drawer"
                        edge="end"
                        onClick={() => setRightDrawer(true)}
                        sx={{ ml: 2, ...(rightDrawer && { display: 'none' }) }}
                    >
                        <MenuIcon/>
                    </IconButton>
                </Toolbar>
            </AppBar>
            <Drawer
                variant="persistent"
                anchor="left"
                open={leftDrawer}
                sx={leftDrawer ? {width: leftDrawerWidth + "px"} : {}}
            >
                <Toolbar />
                <Box sx={{ overflow: 'auto', width: leftDrawerWidth + "px", display: "flex", flexDirection: "column", height: "100%"}}>
                    <List>
                        <ListItem disablePadding>
                            <ListItemButton onClick={() => navigate("/upload-trip")}>
                                <ListItemIcon>
                                    <InboxIcon />
                                </ListItemIcon>
                                <ListItemText primary="Upload Trip" />
                            </ListItemButton>
                        </ListItem>
                    </List>
                    <Box sx={{flexGrow: 1}}/>
                    <Divider />
                    <List>
                        <ListItemButton onClick={() => setLeftDrawer(false)}>
                            <ListItemIcon>
                                <ChevronLeftIcon />
                            </ListItemIcon>
                            <ListItemText primary="Close" />
                        </ListItemButton>
                    </List>
                </Box>
            </Drawer>
            <Box sx={{ flexGrow: 1 }}>
                <Toolbar />
                <StreetMap/>
            </Box>
            <Drawer
                variant="persistent"
                anchor="right"
                open={rightDrawer}
                sx={rightDrawer ? {width: rightDrawerWidth + "px"} : {}}
            >
                <Toolbar />
                <Box sx={{ overflow: 'auto', width: rightDrawerWidth + "px" }}>
                    <IconButton onClick={() => setRightDrawer(false)}>
                        <ChevronRightIcon/>
                    </IconButton>
                </Box>
            </Drawer>
        </Box>
    );
}