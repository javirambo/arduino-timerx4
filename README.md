# arduino-timerx4

_Temporizador de 4 tiempos con Arduino y simple comando_

## Comenzando 🚀

El control del sistema es muy simple.

Se controla solo con 2 botones: Start y Stop.

En estado de reposo (mientras no se pulse ningún botón) el sistema muestra un juego de luces parecido al del auto fantástico kitt (Knight Rider), los 4 leds desplazando de izquierda a derecha. Esto indica que está listo esperando comando.

Si se pulsa 'Start' se puede ir pasando por los 4 leds de indicación de tiempo, para seleccionar el tiempo que desee.

Los tiempos son 5, 10, 15 y 20 minutos. 

Si se deja de pulsar el botón 'Start' por más de 5 segundos, se inicia el temporizador, justo en el tiempo en que quedó encendido el led.

En cualquier momento que se pulse el botón de 'Stop', el sistema aborta cualquier proceso y se resetea, apagando todas las salidas.


## El circuito lo podés encontrar acá 🤖

https://micro57.wordpress.com/2018/03/21/temporizador-de-4-tiempos-con-arduino/

