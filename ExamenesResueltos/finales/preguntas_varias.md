## Pregunta 1

### Consigna

a) El invariante de representación suele escribirse de manera formal y eso permite utilizarlo para una serie de cosas. Si se escribiese en castellano, ¿cuáles de esas cosas se podrían seguir haciendo y cuáles no? Justifique.  

b) Si el invariante de un tipo resultase programable, ¿lo haría? ¿para qué lo usaría? Justifique.

### Resolución

b) Sería una buena idea para chequear que un tipo fuera válido en todo momento para que, por ejemplo, si el usuario de este tipo quisiera aplicarle una función que rompiera el invariante, se pudiera detectar este problema para retornar una excepción, pues no se podrá seguir trabajando apropiadamente con esta estructura. Otra forma de tratar esto sería, en vez de frenar la ejecución, podría darse un aviso al usuario de que lo que está haciendo no está permitido, para que se mantenga constantemente el invariante de representación a pesar de que el usuario haya intentado violarlo.


## Pregunta 2

### Consigna

Suponiendo que un programador tiene un error en una implementación de un diccionario con hashing doble, de modo que una de las dos funciones devuelve el mismo valor (distinto de 0), describir lo que sucede en cada situación (cuando es la primera función la que está mal y cuando lo es la segunda).  

### Resolución

Hashing doble se define como h(k,i) = (h1(k) + i h2(k)) mod |T|.  

Si h1 da un valor constante, queda h(k,i) = (c + i h2(k)) mod |T|. Cuando i = 0, es decir, en el primer intento de cada clave para ser insertada, el resultado será siempre el mismo por lo que habrá aglomeración. Luego, en los siguientes intentos, cuando i > 0, si hay una colisión, habrá entonces aglomeración secundaria, ya que, como h1 es constante, implica que h1(k1) = h1(k2) -> h(k1,i) = h(k2,i).  

Si h2 es constante, la funcion queda h(k,i) = (h1(k) + i c) mod |T|, cuando haya una colisión en h1 para un mismo intento, entonces habrá algomeración primaria. 