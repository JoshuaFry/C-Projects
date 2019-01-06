
This program generates wonderfull works of art by generating a .pgm image file. It takes in 3 command line arguments, the runnable, a shapeSpecFile.txt, and the .pgm you want to output to. The ShapeSpecFile details the shape type, x,y cooridinates, size and grayscale of the shape. If you wish to try out different amounts of shapes you can generate a shapeSpecFile.txt by
running the program with just the runnable argument ./a.out after compiling and specify how many shapes you want. Then you will need to run the program again with 3 arguments.

ex:
<br/>
<p>
PGMGenerator admin$ ./a.out shapeSpecFile.txt output.pgm <br/>
complete! <br/>
</p>

ex2:
<br/>
<p>
PGMGenerator admin$ ./a.out <br/>
how many shapes?400 <br/>
============================= <br/>
shapeSpecFile.txt file created, rerun program with all args <br/>
i.e. ./a.out shapeSpecFile.txt output.pgm <br/>
============================= <br/>
</p> <br/>


Now you can open the output.pgm to view the generated image!
