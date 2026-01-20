---


---

<h1 id="introducción">Introducción</h1>
<p>La proyecto TUI consiste en tres elementos mediante los cuales se puede crear un interfaz de usuario para terminal potente de una forma rápida y sin necesidad de tener ningún conocimiento de la librería ncurses sobre la que se apoya.</p>
<ul>
<li>El primer elemento del proyecto es la librería <em><strong>libtui</strong></em> que proporciona el recubrimiento del API de ncurses que permite la creación del interfaz mediante la descripción de elementos habituales a cualquier interfaz: paneles, botones …</li>
<li>El segundo elemento es un compilador (<em><strong>tbuild</strong></em>) que traduce la descripción de un interfaz de usuario descrito en formato xml en una aplicación completa y funcional.</li>
<li>Y el último elemento es una aplicación gráfica (<em><strong>tui</strong></em>) realizada utilizando la librería libtui y mediante la cual podremos construir el interfaz de nuestro proyecto de forma visual.</li>
</ul>
<h1 id="modelo">Modelo</h1>
<p>El proyecto se basa en un modelo de vistas,.<br>
Actualmente se pueden manejar tres tipos de vistas:</p>
<ul>
<li class="task-list-item">
<p><input type="checkbox" class="task-list-item-checkbox" disabled=""> Vista panel**,  que consiste básicamente en un lienzo sobre el<br>
que se podrán representar los siguientes elementos:</p>
</li>
<li>
<p>Elemento <strong>etiqueta</strong>,  para los textos fijos de nuestro interfaz.</p>
</li>
<li>
<p>Elemento <strong>botón</strong>, para los botones de la aplicación.</p>
</li>
<li>
<p>Elemento <strong>check-button,</strong> para los botones de marcado.</p>
</li>
<li>
<p>Elemento <strong>list-button</strong>, para las listas de selección.</p>
</li>
<li>
<p>Elemento <strong>field</strong>, para aquellos campos que deba rellenar el<br>
usuario.</p>
</li>
<li class="task-list-item">
<p><input type="checkbox" class="task-list-item-checkbox" disabled=""> Vista table, que permite la representación de datos mediante<br>
listas tabuladas.</p>
</li>
<li class="task-list-item">
<p><input type="checkbox" class="task-list-item-checkbox" disabled=""> Vista <strong>edit</strong>, que consiste en un editor simple mediante el cual<br>
manejar ficheros o textos sin formato.</p>
</li>
</ul>
<h2 id="ciclo-de-vida">Ciclo de Vida</h2>
<p>Las vistas tendrán los siguiente estados:</p>
<ul>
<li>Creación, las vistas se crearán al comienzo de la aplicación de<br>
acuerdo a sus propiedades iniciales, tamaño, color, …<br>
Conjuntamente con la vista se crearán los elementos asociados si los<br>
hubiera.</li>
<li>Mostrado, las vistas se mostrarán en el momento asociado a los<br>
eventos de teclado (o ratón) indicados en la descripción del<br>
proyecto.</li>
<li>Activación, esto aplica a la vista completa o a un elemento dentro de<br>
ella si hay varios y significará que este elemento pasa a controlar<br>
los eventos de usuario. El elemento activo se muestra en video<br>
inverso para que el usuario comprenda que esta activo.</li>
<li>Des-activación, cuando se navegue de un elemento a otro se<br>
desactivara el elemento activo previamente a la activación del<br>
siguiente.</li>
<li>Ocultación, al pasar a activar una nueva vista  las vistas<br>
actualmente visibles se ocultarán de acuerdo a una gestión de niveles<br>
de forma tal que cualquier vista con un nivel superior será ocultada.</li>
<li>Destrucción, en el caso de destrucción además de ocultarse se<br>
borrarán todos los datos introducidos que de otra forma permanecerían si volviera a mostrase la vista.</li>
</ul>
<p>El ciclo de vida por tanto será</p>
<pre><code>creación-&gt;mostrado-&gt;activación-&gt;desactivacion-&gt;hide/destroy
        -&gt; mostrado-&gt;..........................
</code></pre>
<h2 id="eventos">Eventos</h2>
<p>El elemento activo gestionará los eventos de entrada que se produzcan.</p>
<p>Se consideran los siguiente posibles eventos asociados a la entrada de teclado:</p>
<ul>
<li>Enter, o entrar.</li>
<li>Out, o salir.</li>
<li>Up, ir  arriba.</li>
<li>Down, ir abajo.</li>
<li>Left, ir a la izquierda.</li>
<li>Right, ir a la derecha.</li>
<li>Next, o siguiente en la lista.</li>
<li>Previous, o anterior en la lista.</li>
<li>Fn, o tecla de Función.</li>
</ul>
<p>Cuando corresponda se trataran internamente (no son configurables) los siguientes eventos:</p>
<ul>
<li>
<p>PgUp, pagina arriba.</p>
</li>
<li>
<p>PgDw, pagina abajo.</p>
</li>
<li>
<p>Init, ir al inicio.</p>
</li>
<li>
<p>End, ir al final.</p>
</li>
<li>
<p>Ins, insert/replace.</p>
</li>
<li>
<p>Backspace, borrar atrás.</p>
</li>
<li>
<p>Del, borrar adelante.</p>
<p>Adicionalmente si permitimos el uso del ratón:<br>
El botón izquierdo se traducirá como enter y el botón derecho como out de forma general.<br>
El botón central se traducirá como Up/Dw en las vistas de tabla y edicción.</p>
<p><em>Además el ratón permitirá la navegación o activación entre elementos dentro la vista o vistas que se estén mostrando.</em></p>
</li>
</ul>
<h1 id="empezando">Empezando</h1>
<p>A continuación se describirá como realizar una aplicación utilizando tUI para ello arrancamos el interfaz gráfico de usuario tui:<br>
<img src="./doc/tui-1.jpg" alt="empezando"></p>
<p>y creamos un nuevo proyecto con Proyect-&gt;new<br>
si lo salvamos podremos observar que en el fichero xml generado:</p>
&lt;?xml version="1.0"?&gt;
<pre><code>&lt;TUI xmlns:tui="http://tui"&gt;
        &lt;Proyect&gt;
                &lt;Name&gt;firstProyect&lt;/Name&gt;
                &lt;Description&gt;First Proyect with tUI&lt;/Description&gt;
        &lt;/Proyect&gt;
&lt;/TUI&gt;
</code></pre>
<h1 id="propiedades">Propiedades</h1>
<p>Como primer paso es conveniente hablar de la configuración o parametrización que permite el proyecto.</p>
<p><img src="./doc/tui-2.jpg" alt="Properties"></p>
<h2 id="color">Color</h2>
<p>La aplicación permite el uso de color por parte de las aplicaciones, pero no todos los terminales admiten o permiten colores.<br>
Para los casos “normales” esto no tiene importancia simplemente nuestra aplicación se vera en blanco y negro independientemente de los colores que se hayan utilizado.<br>
El inicializar el bloque de color se indicara si se admite el uso de color o no.</p>
<p>El API para ello en la librería  libtui es la llamada:</p>
<pre><code>int COLOR_inicializar(unsigned short useColor)
</code></pre>
<p>En el fichero xml se indicará la etiqueta</p>
<pre><code> &lt;Color/&gt;
</code></pre>
<p>para indicar que se admite el uso de colores</p>
<p>Con la  herramienta visual tUI marcaremos “<strong>Use Color</strong>” en el apartado General-&gt;properties.</p>
<h2 id="ratón">Ratón</h2>
<p>La aplicación permite la inter-actuación mediante el ratón pero esto puede ser contraproducente en determinados casos.</p>
<p>Por defecto la aplicación hará uso del ratón como elemento valido de inter-acción si no desea está facilidad puede anularse para ello:</p>
<p>El API en la librería es:</p>
<pre><code>void KEYS_setMouse(int mouse)
</code></pre>
<p>En el fichero xml se indicará la etiqueta</p>
<pre><code>&lt;Mouse/&gt;
</code></pre>
<p>para indicar que acepta el ratón como método de interacción.</p>
<p>Con la  herramienta visual tUI marcaremos “<strong>Use Mouse</strong>” en el apartado General-&gt;properties.</p>
<h2 id="errores">Errores</h2>
<p>El proyecto hace uso del modulo “<strong>error.c</strong>” para gestionar los errores que se detecten.<br>
Este modulo se inicializa mediante la llamada:</p>
<pre><code>void ERR_printError(int print,char * file)
</code></pre>
<p>En la que indicamos si hay que imprimir los errores y en caso de que aplique el fichero donde escribir.</p>
<p>Si optamos por no imprimir los errores el programador puede usar los métodos:</p>
<pre><code>int ERR_isError()
int ERR_lastError()
</code></pre>
<p>En e caso de indicar que se desea imprimir los errores pero no se indica fichero (NULL) se utilizará el stdout.</p>
<p>En el fichero xml de nuestro proyecto esto se indicará con la etiqueta:</p>
<pre><code>&lt;Error&gt;errores.txt&lt;/Error&gt;
</code></pre>
<p>que incluye el fichero donde escribir los errores.</p>
<p>Con la  herramienta visual tUI marcaremos “<strong>Print Errors</strong>” e indicarameos el fichero  en el apartado General-&gt;properties.</p>
<h2 id="check-buttón">Check buttón</h2>
<p>Los check buttón funcionan mediante tres caracteres:</p>
<p>El carácter dentro de un texto que indicara la/s posición/es de marcado.<br>
El carácter a mostrar cuando el elemento no esta marcado.<br>
El carácter a mostrar cuando el elemento este marcado.</p>
<p>Aunque como veremos esto puede cambiarse en cada check-button, esta parametrización permite cambiar los valores por defecto ?,X,_ por por ejemplo ?,Y,N de forma general y que no haya que indicarlo en cada check-button.</p>
<p>El API para ellos es:</p>
<pre><code>void VISUAL_changeCheck(int check,int is_check, int no_check)
</code></pre>
<p>En el xml lo mismo se logrará con la etiqueta:</p>
<pre><code>&lt;Check chCheck="63" chIsCheck="89" chNoCheck="78" /&gt;
or
&lt;Check chCheck="?" chIsCheck="Y" chNoCheck="N" /&gt;
</code></pre>
<p>Con la  herramienta visual tUI indicaremos los caracteres adecuados Ch. Check , Ch is Check, Ch is not Check " en el apartado General-&gt;properties.</p>
<h2 id="border-y-sborder">Border y SBorder</h2>
<p>La aplicación permite crear un border sobre cualquier elemento o vista.<br>
Los borders se describen mediante los caracteres que componen arriba, abajo, izquierda, derecha y las cuatro esquinas, típicamente guiones, barras y el simbolo +.<br>
Para las  vistas de tablas y editor  ( otras en un futuro) donde pueda realizarse scroll se utilizara la descripción de SBorder en lugar de la de Border para tener una referencia visual de cuando es posible hacer scroll.<br>
Los caracteres que configuran estos bordes son parametrizables en la aplicación:</p>
<p>El API para ellos es:</p>
<pre><code>void VISUAL_changeBorder(chtype scroll, chtype chll, chtype chlr, chtype chlu, chtype chld, chtype chlup, chtype chrup, chtype chldw, chtype chrdw);
</code></pre>
<p>Donde el primer parámetro, scroll, indica si nos referimos al border normal (0) o al de scroll (1).</p>
<p>En el xml lo mismo se logrará con la etiqueta:</p>
<pre><code>&lt;Borders Up="45" Dw="45" Lf="124" Rg="124" Cul="43" Cur="43" Cdl="43" Cdr="43"/&gt;
&lt;SBorders Up="45" Dw="45" Lf="124" Rg="35" Cul="43" Cur="43" Cdl="94" Cdr="118"/&gt;
</code></pre>
<p>Con la  herramienta visual tUI indicaremos los caracteres adecuados Border y SBorder en el apartado General-&gt;properties.</p>
<h2 id="user-main">User Main</h2>
<p>Para las inicializaciones necesarias asociadas a nuestra aplicación es posible declarar una función de usuario “main” que se invocará como primera instrucción de programa.<br>
Esta función de manera análoga al main habitual recibirá como parámetros el argc y argv con los que haya invocado el programa.<br>
Si e retorno obtenido es distinto de 0 se procederá a realizar un exit del programa usando este valor como salida.<br>
Esto se declará en el apartado General-&gt;properties y resultará en la siguiente entrada en el xml:</p>
<pre><code>   &lt;Main&gt;userMain&lt;/Main&gt;
</code></pre>
<h2 id="user-end">User End</h2>
<p>Como última instrucción del programa se invocara, caso de existir, la función user-end declarada.<br>
No tiene parámetros de entrada y el resultado de salida se utilizará en el return del main.<br>
Esto se declará en el apartado General-&gt;properties y resultará en la siguiente entrada en el xml:</p>
<pre><code>    &lt;End&gt;userEnd&lt;/End&gt;
</code></pre>
<h2 id="init-view">Init View</h2>
<p>Como init-view se debe indicar la vista a activar en el arranque de la aplicación.<br>
El formato será:</p>
<pre><code>**vista:[elemento]**
</code></pre>
<p>Esto se declará en el apartado General-&gt;properties y resultará en la siguiente entrada en el xml:</p>
<pre><code>   &lt;Init&gt;firstView:firstElement&lt;/Init&gt;
</code></pre>
<h2 id="resumen">Resumen</h2>
<p>El siguiente fichero Xml muestra el resultado de haber fijado las características iniciales de nuestro proyecto:</p>
<pre><code>&lt;?xml version="1.0"?&gt;
&lt;TUI xmlns:tui="http://tui"&gt;
        &lt;Proyect&gt;
                &lt;Name&gt;firstProyect&lt;/Name&gt;
                &lt;Description&gt;First Proyect with tUI&lt;/Description&gt;
                &lt;Main&gt;userMain&lt;/Main&gt;
                &lt;End&gt;userEnd&lt;/End&gt;
                &lt;Init&gt;firstView:firstElement&lt;/Init&gt;
                &lt;Properties&gt;
                        &lt;Color/&gt;
                        &lt;Error&gt;errors.err&lt;/Error&gt;
                        &lt;Check chCheck="63" chIsCheck="89" chNoCheck="78" /&gt;
                        &lt;Borders Up="45" Dw="45" Lf="124" Rg="124" Cul="43" Cur="43" Cdl="43" Cdr="43"/&gt;
                        &lt;SBorders Up="45" Dw="45" Lf="124" Rg="35" Cul="43" Cur="43" Cdl="94" Cdr="118"/&gt;
                &lt;/Properties&gt;
        &lt;/Proyect&gt;
&lt;/TUI&gt;
</code></pre>
<h1 id="keymap">Keymap</h1>
<p>Un punto primordial de cualquier aplicación de terminal es el manejo del teclado y mas concretamente el mapeo de las teclas a los eventos.</p>
<p>De forma más clara que código de teclado traducimos en un evento Enter por ejemplo.</p>
<p>Tradicionalmente esto es una fuente de problemas cuando realizamos una aplicación basada en “ncurses” ya que con alta probabilidad y dependiendo del terminal o la emulación del mismo el termcap o terminfo asociado no este configurado de acuerdo a nuestras necesidades y haya teclas que no funcionen o funcionen de formas distintas según el terminal utilizado.</p>
<p>La aproximación que realizamos en la librería tUI es describir mapas de teclados en los que se puede asociar hasta tres códigos de teclado a un evento.</p>
<p>Estos mapas de teclado residen el el hdr: “mapKey.h” y están pensados para lo que consideramos el caso mas habitual es decir un teclado tipo PC sobre una emulación de xterm.</p>
<p>Sin embargo puede que esto no sea lo más correcto en todos los casos por lo que es posible describir un mapa de teclado propio e indicar su utilización luego en los elementos que gestionan eventos en lugar de los mapa de teclas definidos en la aplicación.</p>
<p>Para ello haremos lo siguiente:</p>
<p>En el caso de utilizar el API directamente:<br>
Rellenar una estructura del tipo <strong>tmapKeys</strong> indicando 0 para no aplica y esta estructura deberá utilizarse posteriormente en la creación de los elementos que vayan a utilizarlo.<br>
En el fichero Xml indicaremos esto mismo de la siguiente manera:</p>
<pre><code>&lt;Keymaps&gt;
        &lt;Keymap Name="myKeymap"&gt;
        &lt;Enter ch1="10" ch2="343" ch3="0"/&gt;
        &lt;Out ch1="27" ch2="0" ch3="0"/&gt;
        &lt;Next ch1="9" ch2="0" ch3="0"/&gt;
        &lt;Previous ch1="353" ch2="0" ch3="0"/&gt;
        &lt;Up ch1="259" ch2="578" ch3="0"/&gt;
        &lt;Down ch1="258" ch2="581" ch3="0"/&gt;
        &lt;Left ch1="260" ch2="579" ch3="0"/&gt;
        &lt;Right ch1="261" ch2="580" ch3="0"/&gt;
        &lt;Fn/&gt;
        &lt;/Keymap&gt;
&lt;/Keymaps&gt;
</code></pre>
<p>Y en el interfaz gráfico haremos uso del menú: General-&gt;Keymap-&gt;new y seguiremos las instrucciones asociadas.</p>
<p><img src="./doc/tui-3.jpg" alt="Keymap"></p>
<h1 id="ed-functions">Ed Functions</h1>
<p>Para los elementos tipo “<strong>fields</strong>”  de entrada de texto deben tener asociada una función de validación o transformación:<br>
La aplicación tiene por defecto asociada las siguientes funciones de validación:</p>
<ul>
<li>numeric, acepta cualquier carácter entre el 48 y el 57 es decir entre 0 y 9.</li>
<li>alfnumeric, acepta caracteres entre 48 y 57, 65-90 y 97-122 es decir<br>
0-9,a-z y A-Z.</li>
<li>7ascii, acepta caracteres entre 32 y 126. tabla ascii 7bits.</li>
</ul>
<p>y las siguientes funciones de trasformación:</p>
<ul>
<li>upper: es un toupper del caracter.</li>
<li>lower,: es un tolower del caracter.</li>
</ul>
<p>Adicionalmente estas funciones tienen asociada dos características:</p>
<ul>
<li>Alineación, derecha para la función numeric, izquierda para el resto.</li>
<li>Modo, inserción/remplazo, en las funciones por defecto siempre es replazo.</li>
</ul>
<p>Si necesitamos una función personal especifica para un determinado campo se puede definir una de la siguiente manera:</p>
<p>Invocación directa a la librería:</p>
<pre><code>int FEDIT_addCheck(unsigned short tipo, unsigned short align,
                unsigned short insert,  int (*checkEdit)(int * caracter))
</code></pre>
<p>Donde el tipo debe ser un número mayor de 16 y distinto para cada función personalizada que identificará la función cuando se utilice.<br>
El parámetro align podrá tener uno de los valores del enumerado EAlign.<br>
El parámetro insert podrá tener uno de los valores del enumerado EInsert.<br>
Y se deberá proporcionar un puntero a la función de usuario que realizara la validación/transformación del carácter introducido por el usuario.<br>
El tipo  se deberá asociar posteriormente en la creación del field.</p>
<p>En el fichero Xml indicaremos esto mismo:</p>
<pre><code>&lt;checksEdit&gt;
     &lt;checkEdit Name="OneTo9" Align="right" Mode="replace" /&gt;
&lt;/checksEdit&gt;
</code></pre>
<p>Y en el interfaz gráfico haremos uso del menú: General-&gt;Ed.Function y seguiremos las instrucciones asociadas.<br>
<img src="./doc/tui-4.jpg" alt="Ed.Function"></p>
<h1 id="colors">Colors</h1>
<h2 id="update-a-publication">Update a publication</h2>
<p>After publishing, StackEdit keeps your file linked to that publication which makes it easy for you to re-publish it. Once you have modified your file and you want to update your publication, click on the <strong>Publish now</strong> button in the navigation bar.</p>
<blockquote>
<p><strong>Note:</strong> The <strong>Publish now</strong> button is disabled if your file has not been published yet.</p>
</blockquote>
<h2 id="manage-file-publication">Manage file publication</h2>
<p>Since one file can be published to multiple locations, you can list and manage publish locations by clicking <strong>File publication</strong> in the <strong>Publish</strong> sub-menu. This allows you to list and remove publication locations that are linked to your file.</p>
<h1 id="markdown-extensions">Markdown extensions</h1>
<p>StackEdit extends the standard Markdown syntax by adding extra <strong>Markdown extensions</strong>, providing you with some nice features.</p>
<blockquote>
<p><strong>ProTip:</strong> You can disable any <strong>Markdown extension</strong> in the <strong>File properties</strong> dialog.</p>
</blockquote>
<h2 id="smartypants">SmartyPants</h2>
<p>SmartyPants converts ASCII punctuation characters into “smart” typographic punctuation HTML entities. For example:</p>

<table>
<thead>
<tr>
<th></th>
<th>ASCII</th>
<th>HTML</th>
</tr>
</thead>
<tbody>
<tr>
<td>Single backticks</td>
<td><code>'Isn't this fun?'</code></td>
<td>‘Isn’t this fun?’</td>
</tr>
<tr>
<td>Quotes</td>
<td><code>"Isn't this fun?"</code></td>
<td>“Isn’t this fun?”</td>
</tr>
<tr>
<td>Dashes</td>
<td><code>-- is en-dash, --- is em-dash</code></td>
<td>– is en-dash, — is em-dash</td>
</tr>
</tbody>
</table><h2 id="katex">KaTeX</h2>
<p>You can render LaTeX mathematical expressions using <a href="https://khan.github.io/KaTeX/">KaTeX</a>:</p>
<p>The <em>Gamma function</em> satisfying <span class="katex--inline"><span class="katex"><span class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML"><semantics><mrow><mi mathvariant="normal">Γ</mi><mo stretchy="false">(</mo><mi>n</mi><mo stretchy="false">)</mo><mo>=</mo><mo stretchy="false">(</mo><mi>n</mi><mo>−</mo><mn>1</mn><mo stretchy="false">)</mo><mo stretchy="false">!</mo><mspace width="1em"></mspace><mi mathvariant="normal">∀</mi><mi>n</mi><mo>∈</mo><mi mathvariant="double-struck">N</mi></mrow><annotation encoding="application/x-tex">\Gamma(n) = (n-1)!\quad\forall n\in\mathbb N</annotation></semantics></math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut" style="height: 1em; vertical-align: -0.25em;"></span><span class="mord">Γ</span><span class="mopen">(</span><span class="mord mathnormal">n</span><span class="mclose">)</span><span class="mspace" style="margin-right: 0.277778em;"></span><span class="mrel">=</span><span class="mspace" style="margin-right: 0.277778em;"></span></span><span class="base"><span class="strut" style="height: 1em; vertical-align: -0.25em;"></span><span class="mopen">(</span><span class="mord mathnormal">n</span><span class="mspace" style="margin-right: 0.222222em;"></span><span class="mbin">−</span><span class="mspace" style="margin-right: 0.222222em;"></span></span><span class="base"><span class="strut" style="height: 1em; vertical-align: -0.25em;"></span><span class="mord">1</span><span class="mclose">)!</span><span class="mspace" style="margin-right: 1em;"></span><span class="mord">∀</span><span class="mord mathnormal">n</span><span class="mspace" style="margin-right: 0.277778em;"></span><span class="mrel">∈</span><span class="mspace" style="margin-right: 0.277778em;"></span></span><span class="base"><span class="strut" style="height: 0.68889em; vertical-align: 0em;"></span><span class="mord mathbb">N</span></span></span></span></span> is via the Euler integral</p>
<p><span class="katex--display"><span class="katex-display"><span class="katex"><span class="katex-mathml"><math xmlns="http://www.w3.org/1998/Math/MathML" display="block"><semantics><mrow><mi mathvariant="normal">Γ</mi><mo stretchy="false">(</mo><mi>z</mi><mo stretchy="false">)</mo><mo>=</mo><msubsup><mo>∫</mo><mn>0</mn><mi mathvariant="normal">∞</mi></msubsup><msup><mi>t</mi><mrow><mi>z</mi><mo>−</mo><mn>1</mn></mrow></msup><msup><mi>e</mi><mrow><mo>−</mo><mi>t</mi></mrow></msup><mi>d</mi><mi>t</mi> <mi mathvariant="normal">.</mi></mrow><annotation encoding="application/x-tex">
\Gamma(z) = \int_0^\infty t^{z-1}e^{-t}dt\,.
</annotation></semantics></math></span><span class="katex-html" aria-hidden="true"><span class="base"><span class="strut" style="height: 1em; vertical-align: -0.25em;"></span><span class="mord">Γ</span><span class="mopen">(</span><span class="mord mathnormal" style="margin-right: 0.04398em;">z</span><span class="mclose">)</span><span class="mspace" style="margin-right: 0.277778em;"></span><span class="mrel">=</span><span class="mspace" style="margin-right: 0.277778em;"></span></span><span class="base"><span class="strut" style="height: 2.32624em; vertical-align: -0.91195em;"></span><span class="mop"><span class="mop op-symbol large-op" style="margin-right: 0.44445em; position: relative; top: -0.001125em;">∫</span><span class="msupsub"><span class="vlist-t vlist-t2"><span class="vlist-r"><span class="vlist" style="height: 1.41429em;"><span class="" style="top: -1.78805em; margin-left: -0.44445em; margin-right: 0.05em;"><span class="pstrut" style="height: 2.7em;"></span><span class="sizing reset-size6 size3 mtight"><span class="mord mtight">0</span></span></span><span class="" style="top: -3.8129em; margin-right: 0.05em;"><span class="pstrut" style="height: 2.7em;"></span><span class="sizing reset-size6 size3 mtight"><span class="mord mtight">∞</span></span></span></span><span class="vlist-s">​</span></span><span class="vlist-r"><span class="vlist" style="height: 0.91195em;"><span class=""></span></span></span></span></span></span><span class="mspace" style="margin-right: 0.166667em;"></span><span class="mord"><span class="mord mathnormal">t</span><span class="msupsub"><span class="vlist-t"><span class="vlist-r"><span class="vlist" style="height: 0.864108em;"><span class="" style="top: -3.113em; margin-right: 0.05em;"><span class="pstrut" style="height: 2.7em;"></span><span class="sizing reset-size6 size3 mtight"><span class="mord mtight"><span class="mord mathnormal mtight" style="margin-right: 0.04398em;">z</span><span class="mbin mtight">−</span><span class="mord mtight">1</span></span></span></span></span></span></span></span></span><span class="mord"><span class="mord mathnormal">e</span><span class="msupsub"><span class="vlist-t"><span class="vlist-r"><span class="vlist" style="height: 0.843556em;"><span class="" style="top: -3.113em; margin-right: 0.05em;"><span class="pstrut" style="height: 2.7em;"></span><span class="sizing reset-size6 size3 mtight"><span class="mord mtight"><span class="mord mtight">−</span><span class="mord mathnormal mtight">t</span></span></span></span></span></span></span></span></span><span class="mord mathnormal">d</span><span class="mord mathnormal">t</span><span class="mspace" style="margin-right: 0.166667em;"></span><span class="mord">.</span></span></span></span></span></span></p>
<blockquote>
<p>You can find more information about <strong>LaTeX</strong> mathematical expressions <a href="http://meta.math.stackexchange.com/questions/5020/mathjax-basic-tutorial-and-quick-reference">here</a>.</p>
</blockquote>
<h2 id="uml-diagrams">UML diagrams</h2>
<p>You can render UML diagrams using <a href="https://mermaidjs.github.io/">Mermaid</a>. For example, this will produce a sequence diagram:</p>
<pre class=" language-mermaid"><svg id="mermaid-svg-NfqrZf3pwn2UiKZw" width="100%" xmlns="http://www.w3.org/2000/svg" height="543" style="max-width: 814px;" viewBox="-50 -10 814 543"><style>#mermaid-svg-NfqrZf3pwn2UiKZw{font-family:"trebuchet ms",verdana,arial,sans-serif;font-size:16px;fill:#000000;}#mermaid-svg-NfqrZf3pwn2UiKZw .error-icon{fill:#552222;}#mermaid-svg-NfqrZf3pwn2UiKZw .error-text{fill:#552222;stroke:#552222;}#mermaid-svg-NfqrZf3pwn2UiKZw .edge-thickness-normal{stroke-width:2px;}#mermaid-svg-NfqrZf3pwn2UiKZw .edge-thickness-thick{stroke-width:3.5px;}#mermaid-svg-NfqrZf3pwn2UiKZw .edge-pattern-solid{stroke-dasharray:0;}#mermaid-svg-NfqrZf3pwn2UiKZw .edge-pattern-dashed{stroke-dasharray:3;}#mermaid-svg-NfqrZf3pwn2UiKZw .edge-pattern-dotted{stroke-dasharray:2;}#mermaid-svg-NfqrZf3pwn2UiKZw .marker{fill:#666;stroke:#666;}#mermaid-svg-NfqrZf3pwn2UiKZw .marker.cross{stroke:#666;}#mermaid-svg-NfqrZf3pwn2UiKZw svg{font-family:"trebuchet ms",verdana,arial,sans-serif;font-size:16px;}#mermaid-svg-NfqrZf3pwn2UiKZw .actor{stroke:hsl(0,0%,83%);fill:#eee;}#mermaid-svg-NfqrZf3pwn2UiKZw text.actor > tspan{fill:#333;stroke:none;}#mermaid-svg-NfqrZf3pwn2UiKZw .actor-line{stroke:#666;}#mermaid-svg-NfqrZf3pwn2UiKZw .messageLine0{stroke-width:1.5;stroke-dasharray:none;stroke:#333;}#mermaid-svg-NfqrZf3pwn2UiKZw .messageLine1{stroke-width:1.5;stroke-dasharray:2,2;stroke:#333;}#mermaid-svg-NfqrZf3pwn2UiKZw #arrowhead path{fill:#333;stroke:#333;}#mermaid-svg-NfqrZf3pwn2UiKZw .sequenceNumber{fill:white;}#mermaid-svg-NfqrZf3pwn2UiKZw #sequencenumber{fill:#333;}#mermaid-svg-NfqrZf3pwn2UiKZw #crosshead path{fill:#333;stroke:#333;}#mermaid-svg-NfqrZf3pwn2UiKZw .messageText{fill:#333;stroke:#333;}#mermaid-svg-NfqrZf3pwn2UiKZw .labelBox{stroke:hsl(0,0%,83%);fill:#eee;}#mermaid-svg-NfqrZf3pwn2UiKZw .labelText,#mermaid-svg-NfqrZf3pwn2UiKZw .labelText > tspan{fill:#333;stroke:none;}#mermaid-svg-NfqrZf3pwn2UiKZw .loopText,#mermaid-svg-NfqrZf3pwn2UiKZw .loopText > tspan{fill:#333;stroke:none;}#mermaid-svg-NfqrZf3pwn2UiKZw .loopLine{stroke-width:2px;stroke-dasharray:2,2;stroke:hsl(0,0%,83%);fill:hsl(0,0%,83%);}#mermaid-svg-NfqrZf3pwn2UiKZw .note{stroke:hsl(60,100%,23.3333333333%);fill:#ffa;}#mermaid-svg-NfqrZf3pwn2UiKZw .noteText,#mermaid-svg-NfqrZf3pwn2UiKZw .noteText > tspan{fill:#333;stroke:none;}#mermaid-svg-NfqrZf3pwn2UiKZw .activation0{fill:#f4f4f4;stroke:#666;}#mermaid-svg-NfqrZf3pwn2UiKZw .activation1{fill:#f4f4f4;stroke:#666;}#mermaid-svg-NfqrZf3pwn2UiKZw .activation2{fill:#f4f4f4;stroke:#666;}#mermaid-svg-NfqrZf3pwn2UiKZw:root{--mermaid-font-family:"trebuchet ms",verdana,arial,sans-serif;}#mermaid-svg-NfqrZf3pwn2UiKZw sequence{fill:apa;}</style><g></g><g><line id="actor3" x1="75" y1="5" x2="75" y2="532" class="actor-line" stroke-width="0.5px" stroke="#999"></line><rect x="0" y="0" fill="#eaeaea" stroke="#666" width="150" height="65" rx="3" ry="3" class="actor"></rect><text x="75" y="32.5" dominant-baseline="central" alignment-baseline="central" class="actor" style="text-anchor: middle; font-size: 14px; font-weight: 400; font-family: Open-Sans, &quot;sans-serif&quot;;"><tspan x="75" dy="0">Alice</tspan></text></g><g><line id="actor4" x1="318" y1="5" x2="318" y2="532" class="actor-line" stroke-width="0.5px" stroke="#999"></line><rect x="243" y="0" fill="#eaeaea" stroke="#666" width="150" height="65" rx="3" ry="3" class="actor"></rect><text x="318" y="32.5" dominant-baseline="central" alignment-baseline="central" class="actor" style="text-anchor: middle; font-size: 14px; font-weight: 400; font-family: Open-Sans, &quot;sans-serif&quot;;"><tspan x="318" dy="0">Bob</tspan></text></g><g><line id="actor5" x1="539" y1="5" x2="539" y2="532" class="actor-line" stroke-width="0.5px" stroke="#999"></line><rect x="464" y="0" fill="#eaeaea" stroke="#666" width="150" height="65" rx="3" ry="3" class="actor"></rect><text x="539" y="32.5" dominant-baseline="central" alignment-baseline="central" class="actor" style="text-anchor: middle; font-size: 14px; font-weight: 400; font-family: Open-Sans, &quot;sans-serif&quot;;"><tspan x="539" dy="0">John</tspan></text></g><defs><marker id="arrowhead" refX="9" refY="5" markerUnits="userSpaceOnUse" markerWidth="12" markerHeight="12" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z"></path></marker></defs><defs><marker id="crosshead" markerWidth="15" markerHeight="8" orient="auto" refX="16" refY="4"><path fill="black" stroke="#000000" stroke-width="1px" d="M 9,2 V 6 L16,4 Z" style="stroke-dasharray: 0, 0;"></path><path fill="none" stroke="#000000" stroke-width="1px" d="M 0,1 L 6,7 M 6,1 L 0,7" style="stroke-dasharray: 0, 0;"></path></marker></defs><defs><marker id="filled-head" refX="18" refY="7" markerWidth="20" markerHeight="28" orient="auto"><path d="M 18,7 L9,13 L14,7 L9,1 Z"></path></marker></defs><defs><marker id="sequencenumber" refX="15" refY="15" markerWidth="60" markerHeight="40" orient="auto"><circle cx="15" cy="15" r="6"></circle></marker></defs><text x="197" y="80" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="messageText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 16px; font-weight: 400;">Hello Bob, how are you?</text><line x1="75" y1="113" x2="318" y2="113" class="messageLine0" stroke-width="2" stroke="none" marker-end="url(#arrowhead)" style="fill: none;"></line><text x="429" y="128" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="messageText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 16px; font-weight: 400;">How about you John?</text><line x1="318" y1="161" x2="539" y2="161" class="messageLine1" stroke-width="2" stroke="none" marker-end="url(#arrowhead)" style="stroke-dasharray: 3, 3; fill: none;"></line><text x="197" y="176" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="messageText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 16px; font-weight: 400;">I am good thanks!</text><line x1="318" y1="209" x2="75" y2="209" class="messageLine1" stroke-width="2" stroke="none" marker-end="url(#crosshead)" style="stroke-dasharray: 3, 3; fill: none;"></line><text x="429" y="224" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="messageText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 16px; font-weight: 400;">I am good thanks!</text><line x1="318" y1="257" x2="539" y2="257" class="messageLine0" stroke-width="2" stroke="none" marker-end="url(#crosshead)" style="fill: none;"></line><g><rect x="564" y="267" fill="#EDF2AE" stroke="#666" width="150" height="84" rx="0" ry="0" class="note"></rect><text x="639" y="272" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="noteText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 14px; font-weight: 400;"><tspan x="639">Bob thinks a long</tspan></text><text x="639" y="288" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="noteText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 14px; font-weight: 400;"><tspan x="639">long time, so long</tspan></text><text x="639" y="304" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="noteText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 14px; font-weight: 400;"><tspan x="639">that the text does</tspan></text><text x="639" y="320" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="noteText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 14px; font-weight: 400;"><tspan x="639">not fit on a row.</tspan></text></g><text x="197" y="366" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="messageText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 16px; font-weight: 400;">Checking with John...</text><line x1="318" y1="399" x2="75" y2="399" class="messageLine1" stroke-width="2" stroke="none" style="stroke-dasharray: 3, 3; fill: none;"></line><text x="307" y="414" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="messageText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 16px; font-weight: 400;">Yes... John, how are you?</text><line x1="75" y1="447" x2="539" y2="447" class="messageLine0" stroke-width="2" stroke="none" style="fill: none;"></line><g><rect x="0" y="467" fill="#eaeaea" stroke="#666" width="150" height="65" rx="3" ry="3" class="actor"></rect><text x="75" y="499.5" dominant-baseline="central" alignment-baseline="central" class="actor" style="text-anchor: middle; font-size: 14px; font-weight: 400; font-family: Open-Sans, &quot;sans-serif&quot;;"><tspan x="75" dy="0">Alice</tspan></text></g><g><rect x="243" y="467" fill="#eaeaea" stroke="#666" width="150" height="65" rx="3" ry="3" class="actor"></rect><text x="318" y="499.5" dominant-baseline="central" alignment-baseline="central" class="actor" style="text-anchor: middle; font-size: 14px; font-weight: 400; font-family: Open-Sans, &quot;sans-serif&quot;;"><tspan x="318" dy="0">Bob</tspan></text></g><g><rect x="464" y="467" fill="#eaeaea" stroke="#666" width="150" height="65" rx="3" ry="3" class="actor"></rect><text x="539" y="499.5" dominant-baseline="central" alignment-baseline="central" class="actor" style="text-anchor: middle; font-size: 14px; font-weight: 400; font-family: Open-Sans, &quot;sans-serif&quot;;"><tspan x="539" dy="0">John</tspan></text></g></svg></pre>
<p>And this will produce a flow chart:</p>
<pre class=" language-mermaid"><svg id="mermaid-svg-XJNqKYbd2EjG0NRX" width="100%" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" height="174.4375" style="max-width: 502.75px;" viewBox="0 0 502.75 174.4375"><style>#mermaid-svg-XJNqKYbd2EjG0NRX{font-family:"trebuchet ms",verdana,arial,sans-serif;font-size:16px;fill:#000000;}#mermaid-svg-XJNqKYbd2EjG0NRX .error-icon{fill:#552222;}#mermaid-svg-XJNqKYbd2EjG0NRX .error-text{fill:#552222;stroke:#552222;}#mermaid-svg-XJNqKYbd2EjG0NRX .edge-thickness-normal{stroke-width:2px;}#mermaid-svg-XJNqKYbd2EjG0NRX .edge-thickness-thick{stroke-width:3.5px;}#mermaid-svg-XJNqKYbd2EjG0NRX .edge-pattern-solid{stroke-dasharray:0;}#mermaid-svg-XJNqKYbd2EjG0NRX .edge-pattern-dashed{stroke-dasharray:3;}#mermaid-svg-XJNqKYbd2EjG0NRX .edge-pattern-dotted{stroke-dasharray:2;}#mermaid-svg-XJNqKYbd2EjG0NRX .marker{fill:#666;stroke:#666;}#mermaid-svg-XJNqKYbd2EjG0NRX .marker.cross{stroke:#666;}#mermaid-svg-XJNqKYbd2EjG0NRX svg{font-family:"trebuchet ms",verdana,arial,sans-serif;font-size:16px;}#mermaid-svg-XJNqKYbd2EjG0NRX .label{font-family:"trebuchet ms",verdana,arial,sans-serif;color:#000000;}#mermaid-svg-XJNqKYbd2EjG0NRX .cluster-label text{fill:#333;}#mermaid-svg-XJNqKYbd2EjG0NRX .cluster-label span{color:#333;}#mermaid-svg-XJNqKYbd2EjG0NRX .label text,#mermaid-svg-XJNqKYbd2EjG0NRX span{fill:#000000;color:#000000;}#mermaid-svg-XJNqKYbd2EjG0NRX .node rect,#mermaid-svg-XJNqKYbd2EjG0NRX .node circle,#mermaid-svg-XJNqKYbd2EjG0NRX .node ellipse,#mermaid-svg-XJNqKYbd2EjG0NRX .node polygon,#mermaid-svg-XJNqKYbd2EjG0NRX .node path{fill:#eee;stroke:#999;stroke-width:1px;}#mermaid-svg-XJNqKYbd2EjG0NRX .node .label{text-align:center;}#mermaid-svg-XJNqKYbd2EjG0NRX .node.clickable{cursor:pointer;}#mermaid-svg-XJNqKYbd2EjG0NRX .arrowheadPath{fill:#333333;}#mermaid-svg-XJNqKYbd2EjG0NRX .edgePath .path{stroke:#666;stroke-width:1.5px;}#mermaid-svg-XJNqKYbd2EjG0NRX .flowchart-link{stroke:#666;fill:none;}#mermaid-svg-XJNqKYbd2EjG0NRX .edgeLabel{background-color:white;text-align:center;}#mermaid-svg-XJNqKYbd2EjG0NRX .edgeLabel rect{opacity:0.5;background-color:white;fill:white;}#mermaid-svg-XJNqKYbd2EjG0NRX .cluster rect{fill:hsl(210,66.6666666667%,95%);stroke:#26a;stroke-width:1px;}#mermaid-svg-XJNqKYbd2EjG0NRX .cluster text{fill:#333;}#mermaid-svg-XJNqKYbd2EjG0NRX .cluster span{color:#333;}#mermaid-svg-XJNqKYbd2EjG0NRX div.mermaidTooltip{position:absolute;text-align:center;max-width:200px;padding:2px;font-family:"trebuchet ms",verdana,arial,sans-serif;font-size:12px;background:hsl(-160,0%,93.3333333333%);border:1px solid #26a;border-radius:2px;pointer-events:none;z-index:100;}#mermaid-svg-XJNqKYbd2EjG0NRX:root{--mermaid-font-family:"trebuchet ms",verdana,arial,sans-serif;}#mermaid-svg-XJNqKYbd2EjG0NRX flowchart{fill:apa;}</style><g><g class="output"><g class="clusters"></g><g class="edgePaths"><g class="edgePath LS-A LE-B" id="L-A-B" style="opacity: 1;"><path class="path" d="M109.66244612068965,67.609375L170.0546875,38.859375L246.125,38.859375" marker-end="url(https://stackedit.io/app#arrowhead5)" style="fill:none"></path><defs><marker id="arrowhead5" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath LS-A LE-C" id="L-A-C" style="opacity: 1;"><path class="path" d="M109.66244612068965,114.328125L170.0546875,143.078125L226.921875,143.078125" marker-end="url(https://stackedit.io/app#arrowhead6)" style="fill:none"></path><defs><marker id="arrowhead6" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath LS-B LE-D" id="L-B-D" style="opacity: 1;"><path class="path" d="M307.84375,38.859375L352.046875,38.859375L400.1027516807447,68.9128733192553" marker-end="url(https://stackedit.io/app#arrowhead7)" style="fill:none"></path><defs><marker id="arrowhead7" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath LS-C LE-D" id="L-C-D" style="opacity: 1;"><path class="path" d="M327.046875,143.078125L352.046875,143.078125L400.1027516807447,114.0246266807447" marker-end="url(https://stackedit.io/app#arrowhead8)" style="fill:none"></path><defs><marker id="arrowhead8" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g></g><g class="edgeLabels"><g class="edgeLabel" transform="translate(170.0546875,38.859375)" style="opacity: 1;"><g transform="translate(-31.8671875,-13.359375)" class="label"><rect rx="0" ry="0" width="63.734375" height="26.71875"></rect><foreignObject width="63.734375" height="26.71875"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span id="L-L-A-B" class="edgeLabel L-LS-A' L-LE-B">Link text</span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><rect rx="0" ry="0" width="0" height="0"></rect><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span id="L-L-A-C" class="edgeLabel L-LS-A' L-LE-C"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><rect rx="0" ry="0" width="0" height="0"></rect><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span id="L-L-B-D" class="edgeLabel L-LS-B' L-LE-D"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><rect rx="0" ry="0" width="0" height="0"></rect><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span id="L-L-C-D" class="edgeLabel L-LS-C' L-LE-D"></span></div></foreignObject></g></g></g><g class="nodes"><g class="node default" id="flowchart-A-24" transform="translate(60.59375,90.96875)" style="opacity: 1;"><rect rx="0" ry="0" x="-52.59375" y="-23.359375" width="105.1875" height="46.71875" class="label-container"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-42.59375,-13.359375)"><foreignObject width="85.1875" height="26.71875"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">Square Rect</div></foreignObject></g></g></g><g class="node default" id="flowchart-B-25" transform="translate(276.984375,38.859375)" style="opacity: 1;"><circle x="-30.859375" y="-23.359375" r="30.859375" class="label-container"></circle><g class="label" transform="translate(0,0)"><g transform="translate(-20.859375,-13.359375)"><foreignObject width="41.71875" height="26.71875"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">Circle</div></foreignObject></g></g></g><g class="node default" id="flowchart-C-27" transform="translate(276.984375,143.078125)" style="opacity: 1;"><rect rx="5" ry="5" x="-50.0625" y="-23.359375" width="100.125" height="46.71875" class="label-container"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-40.0625,-13.359375)"><foreignObject width="80.125" height="26.71875"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">Round Rect</div></foreignObject></g></g></g><g class="node default" id="flowchart-D-29" transform="translate(435.8984375,90.96875)" style="opacity: 1;"><polygon points="58.8515625,0 117.703125,-58.8515625 58.8515625,-117.703125 0,-58.8515625" transform="translate(-58.8515625,58.8515625)" class="label-container"></polygon><g class="label" transform="translate(0,0)"><g transform="translate(-32.03125,-13.359375)"><foreignObject width="64.0625" height="26.71875"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">Rhombus</div></foreignObject></g></g></g></g></g></g></svg></pre>

