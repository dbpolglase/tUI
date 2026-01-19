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
<h1 id="propiedades">Propiedades</h1>
<p>Como primer paso es conveniente hablar de la configuración o parametrización que permite el proyecto.</p>
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
Este modulo se inicializa meante la llamada:</p>
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
<h1 id="vistas">Vistas</h1>
<p>El proyecto se basa en el manejo de vistas, vistas con su ciclo de vida (creación, mostrado, destrucción) y su manejador de eventos asociado.<br>
Actualmente se pueden manejar tres tipos de vistas:</p>
<ul>
<li class="task-list-item"><input type="checkbox" class="task-list-item-checkbox" disabled=""> Vista panel**,  que consiste básicamente en un lienzo sobre el<br>
que se podrán representar los siguientes elementos:</li>
</ul>
<ol>
<li>Elemento <strong>etiqueta</strong>,  para los textos fijos de nuestro interfaz.</li>
<li>Elemento <strong>botón</strong>, para los botones de la aplicación.</li>
<li>Elemento <strong>check-button,</strong> para los botones de marcado.</li>
<li>Elemento <strong>list-button</strong>, para las listas de selección.</li>
<li>Elemento <strong>field</strong>, para aquellos campos que deba rellenar el<br>
usuario.</li>
</ol>
<ul>
<li class="task-list-item">
<p><input type="checkbox" class="task-list-item-checkbox" disabled=""> Vista table, que permite la representación de datos mediante<br>
listas tabuladas.</p>
</li>
<li class="task-list-item">
<p><input type="checkbox" class="task-list-item-checkbox" disabled=""> Vista <strong>edit</strong>, que consiste en un editor simple mediante el cual<br>
manejar ficheros o textos sin formato.</p>
</li>
</ul>
<h2 id="vista-panel">Vista Panel</h2>
<p>The file explorer is accessible using the button in left corner of the navigation bar. You can create a new file by clicking the <strong>New file</strong> button in the file explorer. You can also create folders by clicking the <strong>New folder</strong> button.</p>
<h2 id="switch-to-another-file">Switch to another file</h2>
<p>All your files and folders are presented as a tree in the file explorer. You can switch from one to another by clicking a file in the tree.</p>
<h2 id="rename-a-file">Rename a file</h2>
<p>You can rename the current file by clicking the file name in the navigation bar or by clicking the <strong>Rename</strong> button in the file explorer.</p>
<h2 id="delete-a-file">Delete a file</h2>
<p>You can delete the current file by clicking the <strong>Remove</strong> button in the file explorer. The file will be moved into the <strong>Trash</strong> folder and automatically deleted after 7 days of inactivity.</p>
<h2 id="export-a-file">Export a file</h2>
<p>You can export the current file by clicking <strong>Export to disk</strong> in the menu. You can choose to export the file as plain Markdown, as HTML using a Handlebars template or as a PDF.</p>
<h1 id="synchronization">Synchronization</h1>
<p>Synchronization is one of the biggest features of StackEdit. It enables you to synchronize any file in your workspace with other files stored in your <strong>Google Drive</strong>, your <strong>Dropbox</strong> and your <strong>GitHub</strong> accounts. This allows you to keep writing on other devices, collaborate with people you share the file with, integrate easily into your workflow… The synchronization mechanism takes place every minute in the background, downloading, merging, and uploading file modifications.</p>
<p>There are two types of synchronization and they can complement each other:</p>
<ul>
<li>
<p>The workspace synchronization will sync all your files, folders and settings automatically. This will allow you to fetch your workspace on any other device.</p>
<blockquote>
<p>To start syncing your workspace, just sign in with Google in the menu.</p>
</blockquote>
</li>
<li>
<p>The file synchronization will keep one file of the workspace synced with one or multiple files in <strong>Google Drive</strong>, <strong>Dropbox</strong> or <strong>GitHub</strong>.</p>
<blockquote>
<p>Before starting to sync files, you must link an account in the <strong>Synchronize</strong> sub-menu.</p>
</blockquote>
</li>
</ul>
<h2 id="open-a-file">Open a file</h2>
<p>You can open a file from <strong>Google Drive</strong>, <strong>Dropbox</strong> or <strong>GitHub</strong> by opening the <strong>Synchronize</strong> sub-menu and clicking <strong>Open from</strong>. Once opened in the workspace, any modification in the file will be automatically synced.</p>
<h2 id="save-a-file">Save a file</h2>
<p>You can save any file of the workspace to <strong>Google Drive</strong>, <strong>Dropbox</strong> or <strong>GitHub</strong> by opening the <strong>Synchronize</strong> sub-menu and clicking <strong>Save on</strong>. Even if a file in the workspace is already synced, you can save it to another location. StackEdit can sync one file with multiple locations and accounts.</p>
<h2 id="synchronize-a-file">Synchronize a file</h2>
<p>Once your file is linked to a synchronized location, StackEdit will periodically synchronize it by downloading/uploading any modification. A merge will be performed if necessary and conflicts will be resolved.</p>
<p>If you just have modified your file and you want to force syncing, click the <strong>Synchronize now</strong> button in the navigation bar.</p>
<blockquote>
<p><strong>Note:</strong> The <strong>Synchronize now</strong> button is disabled if you have no file to synchronize.</p>
</blockquote>
<h2 id="manage-file-synchronization">Manage file synchronization</h2>
<p>Since one file can be synced with multiple locations, you can list and manage synchronized locations by clicking <strong>File synchronization</strong> in the <strong>Synchronize</strong> sub-menu. This allows you to list and remove synchronized locations that are linked to your file.</p>
<h1 id="publication">Publication</h1>
<p>Publishing in StackEdit makes it simple for you to publish online your files. Once you’re happy with a file, you can publish it to different hosting platforms like <strong>Blogger</strong>, <strong>Dropbox</strong>, <strong>Gist</strong>, <strong>GitHub</strong>, <strong>Google Drive</strong>, <strong>WordPress</strong> and <strong>Zendesk</strong>. With <a href="http://handlebarsjs.com/">Handlebars templates</a>, you have full control over what you export.</p>
<blockquote>
<p>Before starting to publish, you must link an account in the <strong>Publish</strong> sub-menu.</p>
</blockquote>
<h2 id="publish-a-file">Publish a File</h2>
<p>You can publish your file by opening the <strong>Publish</strong> sub-menu and by clicking <strong>Publish to</strong>. For some locations, you can choose between the following formats:</p>
<ul>
<li>Markdown: publish the Markdown text on a website that can interpret it (<strong>GitHub</strong> for instance),</li>
<li>HTML: publish the file converted to HTML via a Handlebars template (on a blog for example).</li>
</ul>
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
<pre class=" language-mermaid"><svg id="mermaid-svg-7NHslg7VBS5YtMi9" width="100%" xmlns="http://www.w3.org/2000/svg" height="543" style="max-width: 814px;" viewBox="-50 -10 814 543"><style>#mermaid-svg-7NHslg7VBS5YtMi9{font-family:"trebuchet ms",verdana,arial,sans-serif;font-size:16px;fill:#000000;}#mermaid-svg-7NHslg7VBS5YtMi9 .error-icon{fill:#552222;}#mermaid-svg-7NHslg7VBS5YtMi9 .error-text{fill:#552222;stroke:#552222;}#mermaid-svg-7NHslg7VBS5YtMi9 .edge-thickness-normal{stroke-width:2px;}#mermaid-svg-7NHslg7VBS5YtMi9 .edge-thickness-thick{stroke-width:3.5px;}#mermaid-svg-7NHslg7VBS5YtMi9 .edge-pattern-solid{stroke-dasharray:0;}#mermaid-svg-7NHslg7VBS5YtMi9 .edge-pattern-dashed{stroke-dasharray:3;}#mermaid-svg-7NHslg7VBS5YtMi9 .edge-pattern-dotted{stroke-dasharray:2;}#mermaid-svg-7NHslg7VBS5YtMi9 .marker{fill:#666;stroke:#666;}#mermaid-svg-7NHslg7VBS5YtMi9 .marker.cross{stroke:#666;}#mermaid-svg-7NHslg7VBS5YtMi9 svg{font-family:"trebuchet ms",verdana,arial,sans-serif;font-size:16px;}#mermaid-svg-7NHslg7VBS5YtMi9 .actor{stroke:hsl(0,0%,83%);fill:#eee;}#mermaid-svg-7NHslg7VBS5YtMi9 text.actor > tspan{fill:#333;stroke:none;}#mermaid-svg-7NHslg7VBS5YtMi9 .actor-line{stroke:#666;}#mermaid-svg-7NHslg7VBS5YtMi9 .messageLine0{stroke-width:1.5;stroke-dasharray:none;stroke:#333;}#mermaid-svg-7NHslg7VBS5YtMi9 .messageLine1{stroke-width:1.5;stroke-dasharray:2,2;stroke:#333;}#mermaid-svg-7NHslg7VBS5YtMi9 #arrowhead path{fill:#333;stroke:#333;}#mermaid-svg-7NHslg7VBS5YtMi9 .sequenceNumber{fill:white;}#mermaid-svg-7NHslg7VBS5YtMi9 #sequencenumber{fill:#333;}#mermaid-svg-7NHslg7VBS5YtMi9 #crosshead path{fill:#333;stroke:#333;}#mermaid-svg-7NHslg7VBS5YtMi9 .messageText{fill:#333;stroke:#333;}#mermaid-svg-7NHslg7VBS5YtMi9 .labelBox{stroke:hsl(0,0%,83%);fill:#eee;}#mermaid-svg-7NHslg7VBS5YtMi9 .labelText,#mermaid-svg-7NHslg7VBS5YtMi9 .labelText > tspan{fill:#333;stroke:none;}#mermaid-svg-7NHslg7VBS5YtMi9 .loopText,#mermaid-svg-7NHslg7VBS5YtMi9 .loopText > tspan{fill:#333;stroke:none;}#mermaid-svg-7NHslg7VBS5YtMi9 .loopLine{stroke-width:2px;stroke-dasharray:2,2;stroke:hsl(0,0%,83%);fill:hsl(0,0%,83%);}#mermaid-svg-7NHslg7VBS5YtMi9 .note{stroke:hsl(60,100%,23.3333333333%);fill:#ffa;}#mermaid-svg-7NHslg7VBS5YtMi9 .noteText,#mermaid-svg-7NHslg7VBS5YtMi9 .noteText > tspan{fill:#333;stroke:none;}#mermaid-svg-7NHslg7VBS5YtMi9 .activation0{fill:#f4f4f4;stroke:#666;}#mermaid-svg-7NHslg7VBS5YtMi9 .activation1{fill:#f4f4f4;stroke:#666;}#mermaid-svg-7NHslg7VBS5YtMi9 .activation2{fill:#f4f4f4;stroke:#666;}#mermaid-svg-7NHslg7VBS5YtMi9:root{--mermaid-font-family:"trebuchet ms",verdana,arial,sans-serif;}#mermaid-svg-7NHslg7VBS5YtMi9 sequence{fill:apa;}</style><g></g><g><line id="actor3" x1="75" y1="5" x2="75" y2="532" class="actor-line" stroke-width="0.5px" stroke="#999"></line><rect x="0" y="0" fill="#eaeaea" stroke="#666" width="150" height="65" rx="3" ry="3" class="actor"></rect><text x="75" y="32.5" dominant-baseline="central" alignment-baseline="central" class="actor" style="text-anchor: middle; font-size: 14px; font-weight: 400; font-family: Open-Sans, &quot;sans-serif&quot;;"><tspan x="75" dy="0">Alice</tspan></text></g><g><line id="actor4" x1="318" y1="5" x2="318" y2="532" class="actor-line" stroke-width="0.5px" stroke="#999"></line><rect x="243" y="0" fill="#eaeaea" stroke="#666" width="150" height="65" rx="3" ry="3" class="actor"></rect><text x="318" y="32.5" dominant-baseline="central" alignment-baseline="central" class="actor" style="text-anchor: middle; font-size: 14px; font-weight: 400; font-family: Open-Sans, &quot;sans-serif&quot;;"><tspan x="318" dy="0">Bob</tspan></text></g><g><line id="actor5" x1="539" y1="5" x2="539" y2="532" class="actor-line" stroke-width="0.5px" stroke="#999"></line><rect x="464" y="0" fill="#eaeaea" stroke="#666" width="150" height="65" rx="3" ry="3" class="actor"></rect><text x="539" y="32.5" dominant-baseline="central" alignment-baseline="central" class="actor" style="text-anchor: middle; font-size: 14px; font-weight: 400; font-family: Open-Sans, &quot;sans-serif&quot;;"><tspan x="539" dy="0">John</tspan></text></g><defs><marker id="arrowhead" refX="9" refY="5" markerUnits="userSpaceOnUse" markerWidth="12" markerHeight="12" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z"></path></marker></defs><defs><marker id="crosshead" markerWidth="15" markerHeight="8" orient="auto" refX="16" refY="4"><path fill="black" stroke="#000000" stroke-width="1px" d="M 9,2 V 6 L16,4 Z" style="stroke-dasharray: 0, 0;"></path><path fill="none" stroke="#000000" stroke-width="1px" d="M 0,1 L 6,7 M 6,1 L 0,7" style="stroke-dasharray: 0, 0;"></path></marker></defs><defs><marker id="filled-head" refX="18" refY="7" markerWidth="20" markerHeight="28" orient="auto"><path d="M 18,7 L9,13 L14,7 L9,1 Z"></path></marker></defs><defs><marker id="sequencenumber" refX="15" refY="15" markerWidth="60" markerHeight="40" orient="auto"><circle cx="15" cy="15" r="6"></circle></marker></defs><text x="197" y="80" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="messageText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 16px; font-weight: 400;">Hello Bob, how are you?</text><line x1="75" y1="113" x2="318" y2="113" class="messageLine0" stroke-width="2" stroke="none" marker-end="url(#arrowhead)" style="fill: none;"></line><text x="429" y="128" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="messageText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 16px; font-weight: 400;">How about you John?</text><line x1="318" y1="161" x2="539" y2="161" class="messageLine1" stroke-width="2" stroke="none" marker-end="url(#arrowhead)" style="stroke-dasharray: 3, 3; fill: none;"></line><text x="197" y="176" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="messageText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 16px; font-weight: 400;">I am good thanks!</text><line x1="318" y1="209" x2="75" y2="209" class="messageLine1" stroke-width="2" stroke="none" marker-end="url(#crosshead)" style="stroke-dasharray: 3, 3; fill: none;"></line><text x="429" y="224" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="messageText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 16px; font-weight: 400;">I am good thanks!</text><line x1="318" y1="257" x2="539" y2="257" class="messageLine0" stroke-width="2" stroke="none" marker-end="url(#crosshead)" style="fill: none;"></line><g><rect x="564" y="267" fill="#EDF2AE" stroke="#666" width="150" height="84" rx="0" ry="0" class="note"></rect><text x="639" y="272" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="noteText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 14px; font-weight: 400;"><tspan x="639">Bob thinks a long</tspan></text><text x="639" y="288" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="noteText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 14px; font-weight: 400;"><tspan x="639">long time, so long</tspan></text><text x="639" y="304" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="noteText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 14px; font-weight: 400;"><tspan x="639">that the text does</tspan></text><text x="639" y="320" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="noteText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 14px; font-weight: 400;"><tspan x="639">not fit on a row.</tspan></text></g><text x="197" y="366" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="messageText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 16px; font-weight: 400;">Checking with John...</text><line x1="318" y1="399" x2="75" y2="399" class="messageLine1" stroke-width="2" stroke="none" style="stroke-dasharray: 3, 3; fill: none;"></line><text x="307" y="414" text-anchor="middle" dominant-baseline="middle" alignment-baseline="middle" class="messageText" dy="1em" style="font-family: &quot;trebuchet ms&quot;, verdana, arial, sans-serif; font-size: 16px; font-weight: 400;">Yes... John, how are you?</text><line x1="75" y1="447" x2="539" y2="447" class="messageLine0" stroke-width="2" stroke="none" style="fill: none;"></line><g><rect x="0" y="467" fill="#eaeaea" stroke="#666" width="150" height="65" rx="3" ry="3" class="actor"></rect><text x="75" y="499.5" dominant-baseline="central" alignment-baseline="central" class="actor" style="text-anchor: middle; font-size: 14px; font-weight: 400; font-family: Open-Sans, &quot;sans-serif&quot;;"><tspan x="75" dy="0">Alice</tspan></text></g><g><rect x="243" y="467" fill="#eaeaea" stroke="#666" width="150" height="65" rx="3" ry="3" class="actor"></rect><text x="318" y="499.5" dominant-baseline="central" alignment-baseline="central" class="actor" style="text-anchor: middle; font-size: 14px; font-weight: 400; font-family: Open-Sans, &quot;sans-serif&quot;;"><tspan x="318" dy="0">Bob</tspan></text></g><g><rect x="464" y="467" fill="#eaeaea" stroke="#666" width="150" height="65" rx="3" ry="3" class="actor"></rect><text x="539" y="499.5" dominant-baseline="central" alignment-baseline="central" class="actor" style="text-anchor: middle; font-size: 14px; font-weight: 400; font-family: Open-Sans, &quot;sans-serif&quot;;"><tspan x="539" dy="0">John</tspan></text></g></svg></pre>
<p>And this will produce a flow chart:</p>
<pre class=" language-mermaid"><svg id="mermaid-svg-ZBWT2Nh7yrla0eQH" width="100%" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" height="174.4375" style="max-width: 502.75px;" viewBox="0 0 502.75 174.4375"><style>#mermaid-svg-ZBWT2Nh7yrla0eQH{font-family:"trebuchet ms",verdana,arial,sans-serif;font-size:16px;fill:#000000;}#mermaid-svg-ZBWT2Nh7yrla0eQH .error-icon{fill:#552222;}#mermaid-svg-ZBWT2Nh7yrla0eQH .error-text{fill:#552222;stroke:#552222;}#mermaid-svg-ZBWT2Nh7yrla0eQH .edge-thickness-normal{stroke-width:2px;}#mermaid-svg-ZBWT2Nh7yrla0eQH .edge-thickness-thick{stroke-width:3.5px;}#mermaid-svg-ZBWT2Nh7yrla0eQH .edge-pattern-solid{stroke-dasharray:0;}#mermaid-svg-ZBWT2Nh7yrla0eQH .edge-pattern-dashed{stroke-dasharray:3;}#mermaid-svg-ZBWT2Nh7yrla0eQH .edge-pattern-dotted{stroke-dasharray:2;}#mermaid-svg-ZBWT2Nh7yrla0eQH .marker{fill:#666;stroke:#666;}#mermaid-svg-ZBWT2Nh7yrla0eQH .marker.cross{stroke:#666;}#mermaid-svg-ZBWT2Nh7yrla0eQH svg{font-family:"trebuchet ms",verdana,arial,sans-serif;font-size:16px;}#mermaid-svg-ZBWT2Nh7yrla0eQH .label{font-family:"trebuchet ms",verdana,arial,sans-serif;color:#000000;}#mermaid-svg-ZBWT2Nh7yrla0eQH .cluster-label text{fill:#333;}#mermaid-svg-ZBWT2Nh7yrla0eQH .cluster-label span{color:#333;}#mermaid-svg-ZBWT2Nh7yrla0eQH .label text,#mermaid-svg-ZBWT2Nh7yrla0eQH span{fill:#000000;color:#000000;}#mermaid-svg-ZBWT2Nh7yrla0eQH .node rect,#mermaid-svg-ZBWT2Nh7yrla0eQH .node circle,#mermaid-svg-ZBWT2Nh7yrla0eQH .node ellipse,#mermaid-svg-ZBWT2Nh7yrla0eQH .node polygon,#mermaid-svg-ZBWT2Nh7yrla0eQH .node path{fill:#eee;stroke:#999;stroke-width:1px;}#mermaid-svg-ZBWT2Nh7yrla0eQH .node .label{text-align:center;}#mermaid-svg-ZBWT2Nh7yrla0eQH .node.clickable{cursor:pointer;}#mermaid-svg-ZBWT2Nh7yrla0eQH .arrowheadPath{fill:#333333;}#mermaid-svg-ZBWT2Nh7yrla0eQH .edgePath .path{stroke:#666;stroke-width:1.5px;}#mermaid-svg-ZBWT2Nh7yrla0eQH .flowchart-link{stroke:#666;fill:none;}#mermaid-svg-ZBWT2Nh7yrla0eQH .edgeLabel{background-color:white;text-align:center;}#mermaid-svg-ZBWT2Nh7yrla0eQH .edgeLabel rect{opacity:0.5;background-color:white;fill:white;}#mermaid-svg-ZBWT2Nh7yrla0eQH .cluster rect{fill:hsl(210,66.6666666667%,95%);stroke:#26a;stroke-width:1px;}#mermaid-svg-ZBWT2Nh7yrla0eQH .cluster text{fill:#333;}#mermaid-svg-ZBWT2Nh7yrla0eQH .cluster span{color:#333;}#mermaid-svg-ZBWT2Nh7yrla0eQH div.mermaidTooltip{position:absolute;text-align:center;max-width:200px;padding:2px;font-family:"trebuchet ms",verdana,arial,sans-serif;font-size:12px;background:hsl(-160,0%,93.3333333333%);border:1px solid #26a;border-radius:2px;pointer-events:none;z-index:100;}#mermaid-svg-ZBWT2Nh7yrla0eQH:root{--mermaid-font-family:"trebuchet ms",verdana,arial,sans-serif;}#mermaid-svg-ZBWT2Nh7yrla0eQH flowchart{fill:apa;}</style><g><g class="output"><g class="clusters"></g><g class="edgePaths"><g class="edgePath LS-A LE-B" id="L-A-B" style="opacity: 1;"><path class="path" d="M109.66244612068965,67.609375L170.0546875,38.859375L246.125,38.859375" marker-end="url(https://stackedit.io/app#arrowhead5)" style="fill:none"></path><defs><marker id="arrowhead5" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath LS-A LE-C" id="L-A-C" style="opacity: 1;"><path class="path" d="M109.66244612068965,114.328125L170.0546875,143.078125L226.921875,143.078125" marker-end="url(https://stackedit.io/app#arrowhead6)" style="fill:none"></path><defs><marker id="arrowhead6" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath LS-B LE-D" id="L-B-D" style="opacity: 1;"><path class="path" d="M307.84375,38.859375L352.046875,38.859375L400.1027516807447,68.9128733192553" marker-end="url(https://stackedit.io/app#arrowhead7)" style="fill:none"></path><defs><marker id="arrowhead7" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath LS-C LE-D" id="L-C-D" style="opacity: 1;"><path class="path" d="M327.046875,143.078125L352.046875,143.078125L400.1027516807447,114.0246266807447" marker-end="url(https://stackedit.io/app#arrowhead8)" style="fill:none"></path><defs><marker id="arrowhead8" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g></g><g class="edgeLabels"><g class="edgeLabel" transform="translate(170.0546875,38.859375)" style="opacity: 1;"><g transform="translate(-31.8671875,-13.359375)" class="label"><rect rx="0" ry="0" width="63.734375" height="26.71875"></rect><foreignObject width="63.734375" height="26.71875"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span id="L-L-A-B" class="edgeLabel L-LS-A' L-LE-B">Link text</span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><rect rx="0" ry="0" width="0" height="0"></rect><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span id="L-L-A-C" class="edgeLabel L-LS-A' L-LE-C"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><rect rx="0" ry="0" width="0" height="0"></rect><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span id="L-L-B-D" class="edgeLabel L-LS-B' L-LE-D"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><rect rx="0" ry="0" width="0" height="0"></rect><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span id="L-L-C-D" class="edgeLabel L-LS-C' L-LE-D"></span></div></foreignObject></g></g></g><g class="nodes"><g class="node default" id="flowchart-A-24" transform="translate(60.59375,90.96875)" style="opacity: 1;"><rect rx="0" ry="0" x="-52.59375" y="-23.359375" width="105.1875" height="46.71875" class="label-container"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-42.59375,-13.359375)"><foreignObject width="85.1875" height="26.71875"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">Square Rect</div></foreignObject></g></g></g><g class="node default" id="flowchart-B-25" transform="translate(276.984375,38.859375)" style="opacity: 1;"><circle x="-30.859375" y="-23.359375" r="30.859375" class="label-container"></circle><g class="label" transform="translate(0,0)"><g transform="translate(-20.859375,-13.359375)"><foreignObject width="41.71875" height="26.71875"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">Circle</div></foreignObject></g></g></g><g class="node default" id="flowchart-C-27" transform="translate(276.984375,143.078125)" style="opacity: 1;"><rect rx="5" ry="5" x="-50.0625" y="-23.359375" width="100.125" height="46.71875" class="label-container"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-40.0625,-13.359375)"><foreignObject width="80.125" height="26.71875"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">Round Rect</div></foreignObject></g></g></g><g class="node default" id="flowchart-D-29" transform="translate(435.8984375,90.96875)" style="opacity: 1;"><polygon points="58.8515625,0 117.703125,-58.8515625 58.8515625,-117.703125 0,-58.8515625" transform="translate(-58.8515625,58.8515625)" class="label-container"></polygon><g class="label" transform="translate(0,0)"><g transform="translate(-32.03125,-13.359375)"><foreignObject width="64.0625" height="26.71875"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">Rhombus</div></foreignObject></g></g></g></g></g></g></svg></pre>

