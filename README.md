# Practicas de POO 2023
 
Para la realización de las prácticas y la comprobación de los test se ha usado Docker como herramienta. Por lo que si quieres realizar las comprobaciones con los *makefiles* que se incluyen en los diferentes directorios debe tener Docker instalado y descargar la imágen ```diiuca/poo```.

# Como compilar

- En una terminal de Windows con PowerShell, se puede emplear la siguiente orden:
```docker run -it --rm -v $env:USERPROFILE/POO:/home/poo diiuca/poo```

- En cambio, si se emplea una terminal de Windows con CMD, debe emplearse:
```docker run -it --rm -v %USERPROFILE%/POO:/home/poo diiuca/poo```

- En sistemas GNU/Linux, la orden equivalente, sería:
``` docker run -it --rm -v ~/POO:/home/poo diiuca/poo ```

Antes de ejecutarlo asegurese de tener el deamon ejecutandose en su máquina, para hacerlo en Linux:

```sudo systemctl start docker```

Puede que tambien de errores por tema de espacio:

```unlimit -n 2048```

Para saber si pasan todos los tests:

```make test-auto```

Para saber si también pasa los test manuales:

```make tests```

Para hacer el valgrind:

```make valgrind```
