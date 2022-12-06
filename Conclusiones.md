# Conclusiones

Para el desarrollo del videojuego, se busco la implementacion de un contenedor para la distribucion del tablero o almacenar los datos, pero no se encontro algun contenedor 
o estructura de datos que se pudiera implementar (y no complicara innecesariamente), ya que lo que se necesitaba era una matriz bidimenisional con numeros simplemente que fueramos mostrando,
por lo que se opto por esta forma. Despues con los siguientes requerimientos solicitados por el profe de poder regresar la jugada y deshacer ese regreso, se penso en la implementacion de
un stack, ya que por el comportamiento de este contenedor (LIFO) nos servia para sacar el ultimo estado del tablero y tener el anterior como actual o ultimo, hariamos un stack de tableros. Una discupla en este apartado
ya que no logre realizarlo por este metodo, por que al hacer el peek del stack se perdia la referencia del elemento y cuando se queria hacer el rendo del undo habria que guardar matriz unidimensional
en otro stack y se me empezo a complicar la implementacion, por cuestiones de tiempo y en vista del exito no obtenido se opto por una matriz tridimensional donde la tercera dimension nos permitiria ir guardando
la posicion del tablero y las otras dos dimensiones, igual, los volares del tablero. 
Para la parte grafica del juego, se opto por el uso del mouse, ya que el juego de reversi tiene una alta complejididad combinatoria con el numero de posibles juegos que se pueden crear
dependiendo de las fichas con que inicies, y mayor aun conforme va avanzando el juego, cada 'n' fichas tiene 4 opciones maximas para capturar, por lo que la implementacion del teclado, a pesar de ser
mas facil para la lecura de datos, algoritimicamente nos consumiria mas recursos ya que tiene mayor complejidad por el numero de casos.
