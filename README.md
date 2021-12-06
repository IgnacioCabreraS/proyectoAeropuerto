# proyectoAeropuerto
Proyecto Estructura de Datos "GC Airlines" por GC

"GC Airlines" es un programa que simula estar en un aeropuerto, dentro de este podemos comprar un pasaje de avion y elegir que asientos queremos de este, tambien tenemos opciones para revisar el estado de nuestros vuelos, como están organizados los pasajeros, etc. Funciona de una forma dinamica gracias a una hora ficticia, mientras mas tiempo estemos usando las distintas funciones, el tiempo irá pasando, por lo que debes estar atento de tus vuelos comprados.

Como ejecutar el programa:

-La terminal por defecto de windows da problemas a la hora de mostrar los colores que usamos en el codigo, por lo que se debe ejecutar con el Powershell de windows.
-Si se va a ejecutar en Visual Studio o Visual Studio Code use:

gcc -g main.c list.c map.c -o Proyecto
./Proyecto.exe

Cosas a tener en cuenta al usar el programa:

- Funciona con un tiempo ficticio, cada vez que se sale de una funcion, se avanzan 30 minutos.
- El aeropuerto funciona solamente en un horario de 24 horas, cuando sean las 24:00, el programa termina.
- No se pueden comprar 2 pasajes que van al mismo destino.
- No se pueden comprar más asientos en un pasaje ya comprado.
- Los asientos del avion funcionan como una matriz, por lo que tienen coordenada x e y.

Coevaluacion y puntos:

Manuel Cabrera: Trabajo bien aportando en el codigo, aunque falto concentrarse mas en este mismo ademas de ser puntual

Marco Rojas: Trabajo bien en el codigo.

Alexander Guillaume: tuvo un aporte en el trabajo ya que ayudo en algunas cosas, en implementar datos o funciones, pero todavia le falta implementar bien las listas

Ignacio Cabrera: Aportó en gran parte del codigo con las implementaciones de estructuras y TDAS. 


Manuel Cabrera: 0+
Marco Rojas: 0+
Alexander Guillaume: 0+
Ignacio Cabrera: 0+
