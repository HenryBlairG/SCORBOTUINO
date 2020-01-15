# SCORBOTUINO

Este proyecto consiste en generar la documentación necesaria para hacer un controlador para el robot SCORBOT ER VII con una placa Arduino y puentes H.

## Componentes Entregados

* SCORBOT ER VII
* Controlador para SCORBOT ER VII
* Sabertooth 2x32 

## Herramientas Necesarias

* Cautin
* Pinzas
* Alicate
* Osciloscopio
* Fuente de Poder

## Materiales Usados

* 6 puertos D9 Hembra para soldar
* Arduino UNO
* Cable para Protoboard
* Estaño para soldadura
* Optocuplas 4N36

## Diagrama de bajo Nivel

## Pruebas Componentes con Fuente de Poder.

### Prueba para motor DC
El proceso utilizado para probar los motores DC del robot es el siguiente:

1. Configurar Fuente de Poder con un límite de corriente cercano al 10% del valor de corriente pick (En este caso 1.5A) y 0V.
2. Conectar cable tierra en terminal V-- y cable VCC en terminal V++ del motor.
3. Activar contacto en fuente de poder.
4. Incrementar paulatinamente el voltaje en la fuente hasta observar que el eje del motor empieza a rotar.
5. Si la fuente se desactiva por corto circuito, desactivar contacto en fuente de poder y:
  >5.1. Si la corriente límite fue alcanzada, en cuyo caso incrementar el límite levemente y repetir proceso desde el paso 2.
  >
  >5.2. En caso de no alcanzar la corriente límite en esta situación, interrumpir pruebas y buscar cortocircuitos en las conexiones entre la fuente de poder y el motor.

### Prueba para Encoder
El proceso utilizado para probar los encoders del robot es el siguiente:

1. Configurar Fuente de poder para que su corriente y voltaje de salida correspondan a las mencionadas en el datasheet del mismo. Dado que la fuente de poder en esta experiencia tiene un canal fijado en 5V y 3A, la convención del encoder estudiado, se aprovechó el mismo.
2. Conectar sonda de osciloscopio entre la tierra del encoder y un canal del mismo.
3. Activar contacto en fuente de poder.
4. Generar una rotación capaz de activar el encoder (Si el componente tiene eje se hace sobre su eje, de estar conectada a un motor, rotar el eje del motor).
5. Verificar que en la pantalla del osciloscopio se genera el tren de rect apropiado.
6. Si existe otro canal por revisar, repetir proceso desde el paso 2.

### Prueba para Señal Home

| Prueba | Funciona? | 
|:------:|:---------:|
| [Motor 1 y Encoder 1](https://youtu.be/qAPdxo8GyQs) | Si |
| [Motor 2 y Encoder 2](https://youtu.be/4FbdBEUbHtA) | Si |
| [Motor 3 y Encoder 3](https://youtu.be/XapnecsEX7g) | Si |
| [Motor 4 y Encoder 4](https://youtu.be/Zp3o68AthuA) | Si |
| [Motor 5 y Encoder 5](https://youtu.be/IkzQx8U0SOQ) | Si |
| [Motor 6 y Encoder 6](https://youtu.be/s-0CvSOSiwo) | Si |
| Señal Home 1 | Por probar |
| Señal Home 2 | Por probar |
| Señal Home 3 | Por probar |
| Señal Home 4 | Por probar |
| Señal Home 5 | Por probar |
| Señal Home 6 | Por probar |
