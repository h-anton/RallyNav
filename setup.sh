#!/bin/bash
cd app
npm install
npm run build
cd ../server
./gradlew installDist
