import Map from 'ol/Map';
import View from 'ol/View';
import TileLayer from 'ol/layer/Tile';
import OSM from 'ol/source/OSM';
import { useEffect, useState } from 'react';

let lastId = 0;

export default function StreetMap() {
    let [id] = useState("map-" + lastId++)

    useEffect(() => {
        new Map({
            target: id,
            layers: [
              new TileLayer({
                source: new OSM()
              })
            ],
            view: new View({
              center: [0, 0],
              zoom: 2
            })
        });
    }, [id])

    return (
        <div id={id} style={{height: "100%"}}>

        </div>
    )
}