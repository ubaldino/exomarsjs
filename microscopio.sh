#!/bin/bash

DIRECTORIO='./photos/'

# Funcion para capturar
# muestras con el 
# microscopio

function capturar {
    RUTA=$DIRECTORIO/`date +"%Y%m%d%H%M%S"`.jpg
    echo 'capturando imagen en : '$RUTA
    ffmpeg -f v4l2 -s 640x480 -i /dev/video0 -vframes 1 $TS
    echo 'Imagen capturada'
    exit 0
}
capturar

