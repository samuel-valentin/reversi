# Uso de funciones

Rectangle sourceRec creamos una variable que nos ayudara a dibujar la imagen dentro del rectangulo, al ser imagenes del mismo tama;o y rectangulos iguales, se utilza una sola funcion para ambos botones.
Rectangle btnBounds creamos una variable tipo rectangulo que nos define la posicion y tama;o de nuesrto rectangulo

render_board() se inicializa la longitud de la celda y despues la cordenada x,y donde empezara a dibujarse en nuestro tablero
se empiezan dos ciclos de 8 para dibujar un tablero de 8 x 8 con un if intermedio que nos verfica si ya se pinto el cuadro en la posicion que nos encontramos,
si ya lo pintamos, pasamos y pintamos lo que corresponde.

render_pieces () se inicializa de igual manera donde se dibujaran las fichas, en este caos es para encontrar el centro de la casilla, nos dirijimos a render_possible_moves () 
donde recorremos todo el tablero para comprobar si 'x' espacio esta disponible o si es apto para jugar. Una ves que sabemos que espacios se pueden jugar, recorremos todo el tablero 
con dos ciclos for donde vamos haciendo comapraciones y si encuentra un 0 (BLACK_PLAYER) pintamos una ficha negra, un 1 (WHITE_PLAYER) ficha blanca y un 3 (PLAYABLE )un gris.

Ya terminamos de dibujar todo el tablero, por lo que hacemos make_next_move() obtenemos la posecion del mouse y comprobamos si es una posicion valida, si es, incrementamos el score del jugador actual
por la ficha que puso, agregamos la ficha del jugar a la posicion y capuramos la pieza. Dibujamos el score, comprobamos si se ejecuto la jugada para cambiar de jugador y finalmente
reinicializamos las posiciones de x y y, para que el ciclo de comprobacion if no se ejecute indevidamente.

Por ultimo son las funciones de redo_game y undo_game explicadas en las conclusiones a mas profundidad, donde se llaman las funciones y se hace una copia del tablero actual en un "arreglo de tableros", para que cuando hagamos undo, accedamos al tablero de una posecion anterior
y cuando hagamos redo al tablero de la posicion siguiente.
