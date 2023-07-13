# Resumen teórico-práctico de Algoritmos y Estructuras de Datos II
### 1° Cuatrimestre 2023

## 1 - Tipos Abstractos de Datos
Un TAD es un modelo formal matemático definido por un conjunto de valores con sus determinadas operaciones, similar a un anillo matemático. Se especifican en un lenguaje formal para evitar ambigüedades, pensando en el qué hay que hacer o resolver, y no en el cómo hacerlo.

### 1.1 - Partes de un TAD

- **Parámetros formales**: Son los tipos y operaciones requeridas por los TADs paramétricos.
- **Igualdad Observacional**: Define el criterio bajo el cual las instancias de un TAD son indistinguibles. Es parte del metalenguaje, y como tal no puede ser utilizado dentro de los axiomas; se considera que _vive_ fuera del TAD, a diferencia de los observadores básicos, que sí _viven_ dentro del TAD. Se define con los observadores básicos; dos instancias de TAD son iguales si y solo si coinciden observacionalmente. La relación de igualdad que queda definida en el modelo es una _congruencia_ (esto es, cosas que están en la misma _clase de equivalencia_, van a la misma clase de equivalencia sin importar qué función se les aplique).
- **Género**: Es el nombre que recibe el conjunto de valores del tipo.
- **Usa**: Incluye los géneros y operaciones externas con las que interactúa el TAD.
- **Exporta**: Las operaciones y géneros que quedan a disposicion de usuarios del tipo.
- **Generadores**: Son las operaciones que permiten construir valores del tipo. Para ser adecuadas, debe ser posible construir cualquier instancia posible a traves de ellas. Tienen la particularidad de que a partir de una aplicación finita de ellos se pueden construir (o generar, de ahí su nombre) absolutamente todas las instancias del TAD. Contrariamente, nada impide que definamos generadores de más, es decir, que solamente generen instancias que ya podían ser generadas a partir de los otros. Sin embargo, no es recomendable esta práctica, ya que dificultaría bastante la axiomatización de las funciones
- **Observadores Básicos**: Son las operaciones que permiten obtener informacion acerca de las instancias de un tipo. Nos permiten distinguir cuando dos instancias de un TAD se comportan de la misma manera a los efectos de nuestro estudio. Deben ser minimales, es decir, no deberían existir observadores que sólo identifiquen aspectos de la instancia que ya han sido identificado por los otros observadores.
- **Otras Operaciones**: Las operaciones que no son generadores ni observadores.
- **Axiomas**: Son las reglas que definen el comportamiento de las funciones.

### 1.2 - Creación de un TAD
- Se comienza con la **abstracción** de un problema descripto en un lenguaje informal, para poder identificar sus aspectos importantes
- Le sigue la **modularidad**, para evitar bloques de especificación muy grandes en los que se mezclen todas sus características
- La **axiomatización**, en la que se definen los axiomas de los observadores básicos sobre los generadores no restringidos, cubriendo todo su dominio. Las otras operaciones se axiomatizan respecto a los observadores
- La **minimalidad** en la especificación del TAD es fundamental, para evitar las inconsistencias y redundancia

#### 1.2.1 - Otros conceptos importantes en la creación del TAD

La **brecha semántica**, o semantic gap, se refiere a la diferencia que existe entre el lenguaje natural en el que se describe un problema, y su especificación formal y rigurosa en el TAD.  

Algunos aspectos a tener en cuenta en la especificación de TAD son:
- La **congruencia** es importante de mantener en los observadores de un TAD. Dos instancias iguales, al aplicarles un observador básico, deberían devolver el mismo resultado. Si no, rompería su congruencia.   
- El **comportamiento automático** se refiere a aquellas acciones de un problema que se realizan de forma automática o implícita, y **no** deben ser axiomatizados.  
- Evitar la **sobre** o **sub-especificación**. La primera se da cuando hay varias formas de saber cuál es su resultado para unos valores dados de sus parámetros; esto es un problema pues puede romper la congruencia. La segunda se da cuando no hay axiomas bien definidos sobre el comportamiento de una función del TAD. 
- No axiomatizar sobre casos restringidos.  
- No axiomatizar sobre generadores de otros TADs; esto puede ir en contra de la igualdad observacional definida.

Es importante notar que al aplicar un generador recursivo a una instancia de un TAD (e.g.: “Ag(1, ∅)”) no se está modificando la instancia que recibe como parámetro, ya que en nuestro lenguaje abstracto no existe la noción de _cambio de estado_, sino que lo que se está haciendo es generar una nueva instancia basada en la anterior, y cuyo comportamiento podrá ser descripto cuando se apliquen los observadores básicos sobre ella. Recordar el concepto de **transparencia referencial** del paradigma funcional, que indica que los resultados de las funciones sólo dependen de sus argumentos.  

Los axiomas son fórmulas bien formadas según ciertas reglas gramaticales, aplicacadas a los **términos**. Los términos son las variables, constantes y símbolos de funciones aplicadas a términos. Una fórmula bien formada será cerrada si todas sus variables están cuantificadas.  

### 1.3 - Recursión

La idea es que al ir simplificando se llega a un punto donde no se puede simplificar más: el caso base, tal como existe en inducción. Allí la definición (o axioma, para decirlo de acuerdo al contexto donde usaremos recursión) se resuelve directamente sin usar el concepto que se está definiendo, lo importante es que para resolver el caso base nos basta con saber qué tiene que devolver la función para ese caso particular, lo cual es relativamente sencillo.  

Ahora bien, la autoreferencia que hemos dicho caracteriza a las definiciones bien puede darse de manera indirecta. Lo que encontramos en estos casos es recursión mutua; donde una definición no hace autoreferencia directamente sino lo hace a través de otra definición. Claramente, la recursión mutua puede darse en más de dos niveles.

## 2 - Complejidad Computacional

Se refiere al análisis de la complejidad de un algoritmo en **tiempo** y en **espacio**. Se calcula la eficiencia, de forma independiente a la computadora que lo ejecuta, o a su compilador, o a su lenguaje, etc. Se describe respecto al tamaño de entrada o input y a las características de este, con un análisis asintótico.  

Este análisis se puede realizar de dos maneras:
- Empírica: Se miden los recursos utilizados por el computador, el tiempo exacto que llevó su ejecución, la memoria utilizada, etc.
- Teórica: Se basa en en análisis del algoritmo dado un modelo de cómputo, sin necesidad de ejecutar el programa. Vale para toda circunstancia en la que se ejecute.  

### 2.1 - Modelo de cómputo 
Describe la forma en la que una función matemática es computada dado un dominio. En el análisis de complejidad computacional de manera teórica, se utiliza para definir qué operaciones pueden ser ejecutadas en un tiempo acotado por una constante, medido con la cantidad de Operaciones Elementales (OEs). Es una especie de *banco de prueba* universal para implementar un algoritmo.

### 2.2 - Cálculo de complejidad
Para cada algoritmo, se define $t(i)$ la funcion que mide la cantidad de operaciones elementales con un input de instancia $i$. Su complejidad es de $O(1)$.  
Luego, tomamos $T(i)$ como el tiempo que tarda el algoritmo en ser ejecutado para su instancia $i$. Definimos sus cálculos como:

- Condiciones:  
$$T(if\ C\ then\ S_1\ else\ S_2\ end) = T(C) + max{(T(S_1), T(S_2))}$$
- Loops:  
$$T(while\ C\ do\ S\ end) = T(C) + cantIteraciones\ \times (T(S) + T(C))$$  
- Llamadas:
$$T(F(P_1, P_2,...\ , P_n)) = 1 + \sum_{i=1}^{n}{T(P_i) + T(F)}$$  

Utilizamos las notaciones $T_{peor}(n)$,$T_{mejor}(n)$,$T_{prom}(n)$ para definir las complejidades temporales de peor, mejor y caso promedio, para cada algoritmo $A$:  

$T_{peor}(n) = max({t(i) | I ∈ I_A, |I| = n})$  
$T_{mejor}(n) = min({t(i) | I ∈ I_A, |I| = n})$  

### 2.3 - Principio de Invarianza
Dado un algoritmo y dos máquinas $M_1$ y $M_2$ que tardan $T_1(n)$ y $T_2(n)$ en ejecutarlo, respectivamente, sobre inputs de tamaño $n$, existe una constante $c$ tal que $c > 0$ y un $n_0 \in N$ tales que:  
$\forall n \geq n_o \rightarrow T_1(n) \leq c\ T_2(n)$  
Es decir, dos ejecuciones distintas del mismo algoritmo solo difieren en eficiencia en un factor constante para valores de entrada suficientemente grandes.  

### 2.4 - Análisis asintótico
Interesa calcular el orden de magnitud que tiene el tiempo de ejecución de cada algoritmo. A mayor tamaño de input, mayor costo. Las medidas de comportamiento asintótico son:  

- Notación Big $O$, cota superior
- Notación Big $\Omega$, cota superior
- Notación Big $\Theta$, orden exacto


## 3 - Diseño de TADs

Hay que pasar de las descripciones formales y abstractas del TAD, hechas con lenguaje de especificación, a la implementación de estos comportamientos, valores, operaciones y demás características de los TADs. Se pasa del paradigma funcional al paradigma imperativo, más cercano a la programación habitual. El objetivo en la especificación de TADs fue describir el comportamiento del problema a resolver, pero no interesaba determinar cómo lo resolveríamos. Al especificar estamos describiendo el problema, recién al diseñar comenzamos a resolverlo.  

En el paradigma funcional los datos solo tienen sentido en cuanto sean argumentos o resultados de funciones, sin embargo, en el paradigma imperativo, los datos son tratados como entidades independientes de las funciones que los utilizan. Es usual que se trabaje con una instancia de un objeto que se va modificando y cuyos valores anteriores no interesen. Por lo tanto, por cuestiones de optimización y uso, no tiene sentido construir cada vez un objeto nuevo para devolverlo como resultado de una función como sí se hacía en la especificación de TADs.  

Se deben respetar aspectos como la eficiencia en tiempo y espacio, encapsulamiento, ocultamiento de la información privada, ectétera. Para esto hay que discriminar según el **contexto de uso**, lo cual llevará a una determinada solución.  

Se lleva a cabo un diseño jerárquico, es decir, la definición de als representaciones de los tipos en funcion de otras representaciones más simples, separando las responsabilidades en el diseño del TAD.

### 3.1 - Metodología

Desde una manera abstracta, diseñar implica la vinculación entre la abstracción del TAD y su representación a través de una **estructura de datos** y la definición de sus funciones de tipo, asi como también la introducción de los elementos _no funcionales_.  Con el propósito de implementar un _tipo_, deberemos:
- Proveer una representacion para sus valores,
- Definir las funciones del tipo en funcion de las de su representacion,
- Demostrar que las funciones implementadas satisfacen las relaciones especificadas en los axiom

Se deben tener en cuenta los aspectos de la **interfaz** y los servicios exportados, que explican las complejidades de cada función, sus condiciones, aliasing, implementaciones, etc. También son importantes las pautas de implementación, es decir, todo aspecto referido a los medios a través de los cuales el TAD garantiza los aspectos de uso.

### 3.2 - Conceptos importantes

La **transparencia referencial** implica el desarrollo de funciones cuyos resultados depenten exclusivamente de sus parámetros explícitos, como una función matemática. El uso de variables globales o comportamiento no deterministico puede resultas en funciones no referencialmente transparentes.  

El **aliasing** se refiere a la posibilidad de tener un mismo nombre para más de una variable/puntero/referencia/instancias de clase. Se debe comunicar bien esto para evitar modificar resultados no esperados, o utilizar copias como referencias.  

Cuando se habla de ocultamiento de información, en realidad se está hablando indirectamente del **encapsulamiento** o **modularización**. Esto tiene como ventaja que ayuda a la comprensión de la interfaz para el usuario, dando algo más limpio. También alienta al reuso.

### 3.3 - Pasaje de paradigma imperativo a abstracto

Como el lenguaje de implementación es diferente al de especificación en los TADs, es necesario formular algo que indique cuándo algo pasa de un paradigma al otro. Se define para esto la funcion _sombrerito_, $\hat{•}: G_1 \rightarrow G_T$, que indica que, para cada valor imperativo, devuelve el término lógico correspondiente en su paradigma funcional, como el de especificación de TADs.

### 3.4 - Representación

El objetivo de este paso es definir la forma en que representaremos el tipo que estamos diseñando en esta iteración. La elección de una forma de representación está dada por la elección de una o mas estructuras, las cuales deberan estar debidamente justificadas. Ademas de elegir la estructura de representacion, es necesario definir cual es la relación entre la estructura de representacion y el tipo representado. Por ultimo, se deberan proveer los algoritmos que operan sobre la estructura y que resuelven cada una de las operaciones.  

Definir la representación de un módulo implica tener en cuenta:
- Estructura interna sobre la cual se aplican las operaciones
- Relación entre representación y abstracción
- Definición de algoritmos y servicios usados

Un módulo de diseño debe tener la siguiente estructura:
1. Especificación (puede omitirse si es uno de los TADs provistos por la catedra, o incluirse solo los cambios si es una
extension de un TAD ya conocido).
2. Aspectos de la interfaz
     - Servicios exportados: órdenes de complejidad, aspectos de aliasing, efectos secundarios, todo lo que el usuario necesite saber.
     - Interfaz
3. Pautas de implementación
     - Estructura de representación: estructura elegida, justificación, estructuras alternativas, etc.
     - Invariante de Representación
     - Función de Abstracción
     - Algoritmos
4. Servicios usados
     - Ordenes de complejidad, aspectos de aliasing, etc., requeridos de los tipos soporte.

#### 3.4.1 - Estructura de representación

La estructura de representación de las instancias de los tipos sólo será accesible (modificable, consultable) a través de las operaciones que se hayan detallado en la interfaz del módulo de abstracción respectivo, pues sino se **rompería el encapsulamiento**.  

Las variables en un programa referencian valores. Será imposible el acceso a la representación interna de estos, como veremos más adelante, y esto redundará en la _modularidad_ de nuestro diseño y en el _ocultamiento de información_, que nos permite hacer invisibles algunos aspectos que serán encapsulados. Esto es util para aumentar el nivel de abstracción y diseñar código que sea mas facilmente modificable, mantenible y extensible. Al acceder a los objetos solo a través de su interfaz no nos atamos a su implementación, solo a su funcionalidad. 

#### 3.4.2 - Invariante de representación

El invariante de representación es un predicado que determina si la instancia de la estructura representa un elemento válido del género. Determina un estado que se cumple constantemente en cada cambio realizado en la estructura, garantizando que no se rompa en su utilización. Se define como $Rep\ :\ \hat{genero.representado} \rightarrow boolean$.  

Quedan expresados en el las restricciones de coherencia de la estructura, surgidas de la redundancia de informacion que pueda haber. Notemos que su dominio es la imagen funcional del tipo que estamos implementando. Esto es necesario para que podamos “tratar” los elementos del dominio en logica de primer orden. Su imagen no es el genero bool, sino los valores logicos Verdadero y Falso

### 3.5 -  Abstracción

Esta herramienta permite vincular una estructura con algún valor abstracto que representa. Si $T$ es un género abstracto que representa con la estructura $estr$, la función de abstracción se denota como $Abs\ :\ \hat{estr} \rightarrow \hat{T}(Rep(genero.del.tipo))$.  

Es decir, tiene por dominio al conjunto de instancias que son la imagen abstracta del tipo de representación, y devuelve una imagen abstracta de la instancia del tipo representado. Debemos tener en cuenta que:

- Su dominio está restringido a las instancias de la estructura que cumplen el invariante de representación, y es total sobre este dominio.
- No necesita ser inyectiva: dos instancias válidas pueden representar al mismo término de un TAD.
- Debe ser sobreyectiva sobre las clases de equivalencia de la igualdad observacional, al menos con respecto al universo que nos ha restringido nuestro contexto de uso. Si no lo fuera, significaría que hay elementos del tipo que queremos representar que no podrán ser efectivamente representados.
- No necesariamente es sobreyectiva sobre el conjunto de términos de un TAD. Por la forma en la que _Abs_ es construida no es posible diferenciar entre instancias de un TAD que son observacionalmente iguales y por lo tanto no es posible garantizar que todo término del TAD es imagen de _Abs_ para alguna estructura de representación.
- La funcion _Abs_ debe ser un homomorfismo respecto de la estructura del TAD cuando se le aplican algoritmos.

## 4 - Diseño de Conjuntos y Diccionarios

Estos son algunos de los TADs mas importantes de la computación. Podriamos tomar al conjunto como un tipo de diccionario donde no hay valor, sino solo claves. La implementación de estos TADs sobre estructuras secuenciales llevaría a complejidades lineales para operaciones como _borrar()_, _buscar()_ o _añadir()_ elementos. Una buena solución es implementarlos sobre otras estructuras de datos.

### 4.1 - Arbol Binario de Búsqueda (ABB)

Es un binary tree en el que el valor de todos los elementos del subarbol izquierdo es menor que el de la raíz, y el valor de todos los elementos del subrarbol derecho es mayor que el de la raíz, y esto para todos los nodos. Es decir, todo subarbol del ABB debe ser un ABB.  

Las operaciones de _borrar()_, _buscar()_ y _añadir()_ tendrían complejidad logarítmica en caso de que el ABB estuviera distribuído uniformemente, pero esto no se cumple siempre, pues el arbol puede no estarlo. En el peor caso, todo nodo tiene un solo hijo, provocando que los algoritmos requieran recorrer todos los nodos para encontrar el elemento dado; como resultado, la complejidad es lineal.

### 4.2 - Balanceo de Árboles

Un arbol balanceado es aquel en el que todas las ramas del arbol tienen _casi_ la misma altura. Una buena opción sería que la altura de todos los subarboles del arbol varíe en, a lo sumo, 1 unidad.

#### 4.2.1 - Arbol k-ario balanceado

**Caso ideal de arbol k-ario:** el arbol tiene hijos con 0 o $k$ hijos. La longitud de las ramas difiere a lo sumo en 1.  
**Teorema:** un arbol binario perfectamente balanceado de $n$ nodos tiene una altura de $\lfloor log_2(n) \rfloor + 1$. Así, las hojas serán más del 50% de los nodos del árbol.

### 4.3 - AVL

El arbol de Adelson-Velskii-Landis es una implementación de un arbol binario de búsqueda auto-balanceable, en el que, luego de realizar cada operación, el árbol ejecutará **rotaciones** para mantener su propiedad de ser balanceado en altura. Así, dado el árbol AVL $T$, se cumple que:
- $T_{izq}$ es un AVL
- $T_{der}$ es un AVL
- $|H(T_{der}) - H(T_{izq})| \leq 1$

#### 4.3.1 - Factor de balanceo

El FDB de un árbol $T$ se define como la diferencia entre la altura de su subárbol derecho y la de su subárbol izquierdo. Es decir: $FDB(T) = |H(T_{der}) - H(T_{izq})|$

#### 4.3.2 - Rotaciones de AVL y algoritmos

El reequilibrio del AVL se produce de abajo hacia arriba sobre los nodos en los que se produce el desequilibrio. Sus tipos son

- **RR**: Inserción en el subarbol derecho de un hijo derecho.
- **LR**: Inserción en el subarbol izquierdo de un hijo derecho.
- **RL**: Inserción en el subarbol derecho de un hijo izquierdo.
- **LL**: Inserción en el subarbol izquierdo de un hijo izquierdo.

Su complejidad está dada por:

1. Complejidad de buscar la posición del nodo dada: $O(log(n))$
2. Complejidad de recalcular los FDB: $O(log(n))$
3. Complejidad de aplicar los cambios: $O(1)$

Debido a esto, la complejidad de aplicar operaciones como _borrar()_, _buscar()_ y _añadir()_ será logarítmica. Cuando hay que buscar al nodo dado, se busca su posición, cuyo costo es de $O(log(n))$.  

En cambio, cuando hay que modificar el árbol, ya sea eliminando o agregando un nodo (o modificando el valor de un nodo, que puede tomarse como eliminarlo y agregar el nuevo), luego de buscar la posición correspondiente, si aparece un FDB de ±2, se debe aplicar una rotación para balancear nuevamente el AVL. La complejidad así será de $O(2\ log(n)) = O(log(n))$.


## 5 - Tries, búsqueda digital

La idea es utilizar una estructura que tenga una complejidad temporal menos dependiente de la cantidad de claves; que tenga un rendimiento razonable de peor caso y que sea rápido en la práctica. Para esto, hay que poder operar sobre la estructura de las claves, para poder comparar aprtes de ellas.  

Algunas desventajas son que pueden requerir mucha memoria en algunas implementaciones, y ser poco eficientes en lenguajes de alto nivel.

### 5.1 - Árbol de Búsqueda Digital

Tienen un funcionamiento similar al del ABB, pero al realizar comparaciones entre nodos, en vez de utilizar simplemente "<" o ">", comparar partes de la clave, como pueden ser bits o letras de esta.

### 5.2 - Trie

Es un árbol $(k+1)-ario$ para alfabetos de $k$ elementos. Los nodos representan cada elemento del alfabeto. A diferencia de un arbol de búsqueda digital, la estructura del trie es independiente del orden en que se agregan sus claves.   

Por ejemplo, si las claves son _strings_, la cantidad de elementos será acotada si tomamos el alfabeto español. La complejidad en este caso de buscar el significado de una palabra será de $O(|key|)$, es decir, del largo de la palabra a buscar.  

#### 5.2.1 - Tries compactos

Los tries compactos son similares a los tries, pero compactan las cadenas que llevan hacia las hojas. Esto significa que, para cada clave, solo hay nodos internos para el prefijo más largo que comparte con alguna otra clave.

#### 5.2.2 - Tries PATRICIA

Los tries PATRICIA (Practical Algorithm To Retrieve Information Coded In Alphanumeric) son una versión más compacta aun de los tries compactos. En este caso, solo hay nodos en las posiciones donde 2 o más claves difieren, así que se minimiza la cantidad de nodos internos. La altura de un árbol PATRICIA está acotada por el numero de claves ademas de la cota anterior (la longitud de la clave mas larga).

## 6 - Tabla Hash - Diseño de conjunto y diccionario

Una tabla de hash es una implementación de conjunto o diccionario utilizada extensamente en la computación moderna. Es una buena idea para aplicaciones con acceso a memoria secundaria, donde representan el costo predominante en tiempo.  

Es una generalización del concepto de array, en la que se le asocia a cada valor de las claves un índice en un arreglo.  

### 6.1 - Hashing

Para lograr indexar la estructura utilizando otros tipos de datos, se aplica una **funcion de correspondencia** entre el tipo y un entero. Esta transformación depende de la implementación, pero _debe_ ser una función, y es ideal que sea inyectiva, es decir, $x=y \iff f(x)=f(y)$.  

Esta función, llamada _hash_, tiene la forma $h\ :\ K \rightarrow{0,1,...,n-1}$ donde $K$ es el género que contiene a las posibles claves del diccionario y $n$ es el tamaño de la tabla de hash.  

### 6.2 - Problema principal: Colisiones

Una función de hash ideal es aquella en la que no hay un mismo índice para dos claves distintas; es decir, una función **inyectiva**, lo cual implicaría que $|K| \leq n$. Esto no es factible en la oráctica, pues toda tabla de hash debería tener que manejar las **colisiones** entre distintas claves con el mismo hash.  

Más allá de la resolución de las colisiones, una función de hash ideal debería cumplir la propiedad de _uniformidad simple_, que implica que cada elemento de su imagen tiene probabilidad igual o similar a otra de ser resultado de alguna clave. Debido a la dificultad de estimar la distribución de las claves, esta propiedad no suele cumplirse en la práctica, por lo que se intenta encontrar una función independiente de la distribución.

### 6.3 - Resolución de colisiones

Los métodos de resolución de colisiones en funciones de hash siguientes se diferencian por la forma en la que se ubica a los elementos, que da lugar a una posible colisión:

#### 6.3.1 - Direccionamiento cerrado

El direccionamiento cerrado funciona mediante la **concatenación**: a cada posición $i$ del arreglo se le asigna una lista que contiene las claves $k$ (y sus significados asociados). Es decir, cumple que $h(k)=i$.  

La búsqueda e inserción de una clave $k$ entonces requerirá recorrer la lista asociada a $h(k)$ para encontrarla (o verificar que no esté), por lo que la complejidad será lineal. Es decir, las complejidades son de la forma:

- Búsqueda: complejidad lineal asociada a la posición $h(k)$: $O(\text{longitud lista asociada a } h(k))$
- Inserción: al principio de la lista asociada a la posición $h(k)$: $O(1)$
- Borrado: complejidad lineal asociada a la posición $h(k)$ en la que se hará la búsqueda: $O(\text{longitud lista asociada a } h(k))$


Si definimos el _factor de carga_ $\alpha = n/|T|$, con $n$ la cantidad de claves y $|T|$ el tamaño máximo de la tabla, se puede comprobar entonces que:  

- Una búsqueda fallida costará en tiempo promedio $\Theta(1+\alpha)$
- Una búsqueda exitosa costará en tiempo promedio $\Theta(1+\alpha/2)$

#### 6.3.2 - Direccionamiento abierto

En este método, todos los elementos se guardarán directamente en la tabla, y las colisiones se resolverán dentro de la misma.  

Se redefine la función de hashing como $h(k,i)$, que representa la dirección del $i$-ésimo intento de guardar el nuevo elemento. Cuando se intenta añadir un elemento en una posición previamente ocupada, entonces se sigue intentando hasta encontras una posición libre. Una posición libre puede dar _overflow_ si la tabla se llena.  

La forma en la que se relaciona $h(k,i)$ con $h(k,i+1)$ se denomina _método de barrido_, con los que recorreremos la tabla:

- **Barrido lineal**: para recorrer la tabla linealmente usamos $h(k,i) = (h'(k,i)+i)\ mod\ |T|$, donde $h'$ es otra función hash. Es simple, pero propensa a la _aglomeración primaria_: si dos secuencias de barrido tienen una colisión, siguen colisionando, y se producen largos tramos de aglomeración.

- **Barrido cuadrático**: usamos $h(k,i)=(h'(k)+i \times c_1 + i² \times c_2)\ mod\ |T|$, con $c_1$ y $c_2$ constantes. Hay posibilidad de _aglomeración secundaria_: si dos claves colisionan en el primer intento, colisionan siempre.

- **Hashing doble**: la idea es qie el barrido ahora dependa también de la clave. Se define $h(k,i) = (h_1(k)+i h_2(k))\ mod\ |T|$. Reduce los fenómenos de aglomeración secundaria, y no tiene algomeración proimaria. El problema de este barrido es que es ineficiente en su uso del caché de la CPU, debido a que las claves colisionadas podrían quedar en posiciones distantes.

### 6.4 - Funciones hash

Su objetivo es la distribución más uniforme posible de claves.  

El _prehashing_ es la etapa del hashing en la qur se pasa del tipo utilizado como clave a un entero. El método debe definirse para cada tipo deseado, y, como siempre, es deseable que la función tenga pocas colisiones, es decir, que sea inyectiva.

Una vez que se tiene un número, hay distintos métodos de hashing, como:

- **División**: $h(k)=k\ mod\ |T|$. Método de baja complejidad, y de rápida implementación y cálculo. Para evitar colisiones, es ideal que el tamaño de la tabla sea un número primo no muy cercano a una potencia de 2.
- **Partición**: Se particiona la clave $k$ en $k_1, k_2, ..., k_n$ y luego se define $h(k) = f(k_1, k_2, ..., k_n)$ para alguna función $f$. La idea es romper los patrones que tenían los datos para lograr una distribución uniforme.
- **Extracción**: Se usa solamente una parte de la clave calcular la dirección.



## 7 - Cola de prioridad y Heaps

Una priority queue es un TAD que representa a una cola en la que el próximo elemento a desencolar será el de mayor prioridad, segun la condición o definicion de prioridad dada en la estructura. Se puede implementar con diversas estructuras de datos, como por ejemplo una lista (será ineficiente) o un heap.

### 7.1 - Heap

Es una estructura de datos en forma de montículo. Tiene forma de árbol binario balanceado, y, usualmente, es _izquierdista_ (no va a hacer piquetes a la 9 de Julio ni tampoco corta el puente Pueyrredón, sino que en el último nivel del árbol, los nodos estarán hacia la izquierda). Cuando las prioridades son mayores a las de los hijos, se tiene un max-heap, mientras que cuando son menores se tiene un min-heap.

#### 7.1.1 - Implementación y algoritmos

Una implementación eficiente en tiempo y espacio de un heap es con un **array**, en el que se puede acceder a los hijos de una raiz accediendo a las posiciones $2i + 1$ o $2i + 2$, siendo $i$ la posición del nodo padre. Si queremos agrear o eliminar elementos en vez de solo modificarlos, deberíamos usar un arreglo dinámico.  

Otra implementación sería utilizando un arbol binario, donde cada nodo posee un puntero a sus hijos, lo tradicional en estas estructuras.  

En esta estructura, buscar el próximo elemento siempre costará $O(1)$, mientras que encolar o desencolar elementos costará $O(log(n))$. Sin embargo, como no tiene por qué ser como un arbol binario de búsqueda, la búsqueda de un elemento será lineal, costando $O(n)$.

#### 7.1.2 - Invariante

Su invariante de representación será:

1. Forma de balanced binary tree
2. La clave de cada nodo es de mayor (o menor) que la de sus hijos
3. Todo subarbol es un heap
4. Puede o no ser izquierdista

#### 7.1.3. - Array to Heap, algoritmo de Floyd

Una forma de pasar de arreglo a Heap sería crear un heap vacío, y recorrer el arreglo y por cada elemento encolarlo al heap. Esto dará una complejidad de $O(n\ log(n))$. Sin embargo, se puede realizar en complejidad lineal si utilizamos el algoritmo de Floyd, que se basa en _heapificar_ los subárboles del árbol representado por el arreglo, empezando desde el anteúltimo nivel hacia arriba. Esto se logra a través de la operación _sift down_. Si se aplica eso a todos los elementos de atrás hacia adelante, se consigue un heap, con complejidad $O(n)$.

## 8 - Sorting

### 8.1 - Algoritmos de ordenamiento por comparación

#### 8.1.1 - Algoritmos estables

Son aquellos que ordenan los elementos manteniendo el orden inicial en el arreglo, es decir, si dos elementos tienen la misma clave, mantendrán su orden de aparición original. Es útil para cuando se ordenan elementos según distintas claves de cada elemento. 


- Insertion Sort: Para cada elemento, busca donde insertarlo en el subarreglo del comienzo, y lo swappea con el que corresponde.
  - Complejidad: $O(n²)$
- Merge Sort: Sigue la metodología Divide & Conquer. Consiste en separar el arreglo en subarreglo hasta que lleguen a tamaño 1, y allí comenzar a aplicar un merge entre ellos. Así, se irán mergeando los subarreglos del mismo tamaño, hasta llegar al tamaño original, que quedará ordenado completamente.
  - Complejidad: $O(n\ log\ n)$

#### 8.1.2 - Algoritmos estables

- Selection Sort: Selection sort es un algoritmo simple, que se basa en tomar para cada posición el mínimo del subarreglo desordenado y intercambiarlo con el primero. Al finalizar el ciclo anidado, en cada iteración los primeros elementos quedarán ordenados. Podría ser estable, solo si se lo modifica, haciendo que se inserte el elemento mínimo, en vez de swappearlo.
  - Complejidad: $O(n²)$
- Heap Sort: Se basa en aprovechar la estructura de heap. Podr´ıa pensarse como una versión del selection sort, donde primero se heapifica el arreglo (a través del algoritmo de Floyd) y luego se obtiene el elemento m´ınimo en cada iteración desencolando en el heap. 
  - Complejidad: $O(n\ log\ n)$
- Quick Sort: Sigue la metodología de Divide & Conquer, como el Merge Sort. Para cada recursión, se elige un pivote, se van poniendo al principio del arreglo todos los elementos menores al pivote y luego el pivote, haciendo que queden de la derecha todos los mayores y de la izquierda todos los menores.
  - Complejidad: $O(n²)$
  - Complejidad promedio: $O(n\ log\ n)$

### 8.2 - Optimalidad

Para el problema de ordenamiento, se puede demostrar un _lower bound_ de $\Omega(n\ log\ n)$, es decir, la complejidad mínima que tiene que cumplir un algoritmo que lo resuelve. En realidad, la cota vale para algoritmos que están basados en comparaciones: si se cuenta con alguna hipótesis adicional (como elementos acotados por un rango), se pueden implementar algoritmos más rápidos (como counting sort o bucket sort).  

Para demostrar eso, vamos a asumir que todas las comparaciones tienen la forma de $a_i < a_j$, y que el resultado es siempre _verdadero_ o _falso_. Utilizamos la herramienta de árboles de decisión, cuyas ramas representan todos los posibles caminos de cómputo que podría tomar un algoritmo. Los nodos internos representan las distintas comparaciones que se realizan, mientras que cada hoja se corresponde con un posible output del algoritmo. La altura del árbol representa la cantidad máxima de ejecuciones posibles.  

En el caso del ordenamiento, hay una hoja por cada permutación posible, así que tiene $n!$ nodos hoja. Esto implica que la altura mínima es $\Omega(log\ n!) = \Omega(n\ log\ n)$. Por ende, los algoritmos como merge sort y heap sort tiene una complejidad asintóticamente óptima.


## 9 - Divide & Conquer

Dividir y Conquistar es una técnica de diseño de algoritmos basada en la reducción recursiva de un problema en varios subproblemas de la misma forma que el original. El proceso continúa hasta que éstos llegan a ser lo suficientemente sencillos como para que se resuelvan directamente. Al final, las soluciones a cada uno de los subproblemas se combinan para dar una solución al problema original.  

La metodología de separar el algoritmo en una parte de **Dividir** el problema en otros problemas pequeños y resolverlos recursivamente, y luego **Conquistar** combinando las soluciones de los subproblemas formando la solución al problema original, es una buena forma de resolver problemas complejos siempre y cuando esta implementación sea posible y eficiente.

### 9.1 - Análisis de Complejidad

La solución típica es dividir en $a$ subproblemas, de tamaño máximo $n/c$; el costo de determinar subproblemas y unirlos requiere $bn^d$.  

#### Análisis por casos

La complejidad es de la forma:
$$T(n)=bn^d(\sum_{i=0}^{log_cn}(a/{c^d})^i)$$  

Se tienen los siguientes casos:  
1. $Si\ f(n) \in O(n^{log_c(a)-\epsilon})\ para\ \epsilon > 0 \rightarrow T(n) \in \Theta(n^{log_c(a)})$
2. $Si\ f(n) \in \Theta(n^{log_c(a)}) \rightarrow T(n) \in \Theta(n^{log_c(a)}\ log(n))$
3. $Si\ f(n) \in \Omega(n^{log_c(a)+\epsilon})\ para\ \epsilon > 0\ y\ af(n/c)\leq kf(n)\ para\ k < 1\ y\ n\ suficientemente\ grande \rightarrow T(n) \in \Theta(f(n))$
