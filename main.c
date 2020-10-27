#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <stdio.h>

sfImage* obtenerImagen(char* ruta){
    sfImage* imagen;
    imagen = sfImage_createFromFile(ruta);
    return imagen;

}

int comprobacion(sfImage* imagenFile){

    sfVector2u sizeImagen;
    sizeImagen = sfImage_getSize(imagenFile);
    unsigned int x = sizeImagen.x;
    unsigned int y = sizeImagen.y;

    if (x<1000 && x>100 && y<1000 && y>100){
        printf("1\n");
        return 1;

    }else{
        printf("0\n");
        return 0;
    }
}

sfText* obtenerTexto(char* texto1, int size, int color, int posicion, int tipoDeLetra, sfImage* imagenFile){
    int resultado = comprobacion(imagenFile);
    unsigned x;
    unsigned y;
    if (resultado == 1){
        sfVector2u sizeImagen;
        sizeImagen = sfImage_getSize(imagenFile);
        x = sizeImagen.x;
        y = sizeImagen.y;
    }else{
        x = 1000;
        y = 1000;
    }
    sfFont *font;
    sfText *sfTexto1 = NULL;
    sfTexto1 = sfText_create();
    sfText_setString(sfTexto1, texto1);

    switch(size) {
        case 1 :
            sfText_setCharacterSize(sfTexto1, 10);
            break;
        case 2 :
            sfText_setCharacterSize(sfTexto1, 30);
            break;
        case 3 :
            sfText_setCharacterSize(sfTexto1, 50);
            break;
        case 4 :
            sfText_setCharacterSize(sfTexto1, 75);
            break;
        default :
            printf("Size de fuente invalido\n" );
            return NULL;
    }
    switch(color) {
        case 1 :
            sfText_setColor(sfTexto1, sfWhite);
            break;
        case 2 :
            sfText_setColor(sfTexto1, sfRed);
            break;
        case 3 :
            sfText_setColor(sfTexto1, sfBlue);
            break;
        case 4 :
            sfText_setColor(sfTexto1, sfGreen);
            break;
        default :
            printf("Color de fuente invalido\n" );
            return NULL;
    }
    if (posicion ==1){
        sfVector2f pos1 = {0,0+20};
        sfText_setPosition(sfTexto1, pos1);
    }else if (posicion ==2){
        sfVector2f pos2 = {(float)x/2,(float)x/2};
        sfText_setPosition(sfTexto1, pos2);
    }else if(posicion ==3){
        sfVector2f pos3 = {0,(float)y-120};
        sfText_setPosition(sfTexto1, pos3);
    }else{
        printf("Posicion de fuente invalido");
        return NULL;
    }
    switch(tipoDeLetra) {
        case 1 :
            font = sfFont_createFromFile("C:\\Users\\ExtremeTech\\CLionProjects\\Proyecto#1\\TiposDeLetras\\arial.ttf");
            break;
        case 2 :
            font = sfFont_createFromFile("C:\\Users\\ExtremeTech\\CLionProjects\\Proyecto#1\\TiposDeLetras\\malvira.ttf");
            break;
        case 3 :
            font = sfFont_createFromFile("C:\\Users\\ExtremeTech\\CLionProjects\\Proyecto#1\\TiposDeLetras\\times.ttf");
            break;
        case 4 :
            font = sfFont_createFromFile("C:\\Users\\ExtremeTech\\CLionProjects\\Proyecto#1\\TiposDeLetras\\phantom.ttf");
            break;
        default :
            printf("Tipo de fuente invalido\n" );
            return NULL;
    }
    sfText_setFont(sfTexto1,font);
    return sfTexto1;
};

sfSprite* Resize(sfImage* imagenResize){
    sfSprite *sprite = NULL;
    sfTexture *texture = NULL;

    //Dimensiones de la imagen original.
    sfVector2u sizeImagen;
    sizeImagen = sfImage_getSize(imagenResize);
    unsigned int x = sizeImagen.x;
    unsigned int y = sizeImagen.y;


    //Obtener la escala adecuada para tener las dimensiones correctas.
    float escalaX = 1000/(float)x;
    float escalaY = 1000/(float)y;

    //LLenar el vector de la escala.
    sfVector2f escalaAdecuada = {escalaX,escalaY};

    //Se crea la textura.
    texture = sfTexture_createFromImage(imagenResize,NULL);

    //Se crea el sprite.
    sprite = sfSprite_create();

    //Se linkea el sprite a la textura.
    sfSprite_setTexture(sprite, texture, sfTrue);

    //Se le aplica una escala al sprite.
    sfSprite_setScale(sprite,escalaAdecuada);

    //Se obtienen los nuevos valores de la imagen.
    return sprite;
}

void guardarImagen(sfImage* imagenFile, sfText* texto1, sfText* texto2, char* ruta){
    //Variables de sprite y texture
    sfSprite *sprite = NULL;
    sfTexture *texture = NULL;


    //Hacemos una comprobacion del tamaño del archivo.
    //1 representa que esa imagen esta permitida.
    int resultadoComprobacion = comprobacion(imagenFile);
    if (resultadoComprobacion == 1){
        sfVector2u sizeImagen;
        sizeImagen = sfImage_getSize(imagenFile);
        unsigned int x = sizeImagen.x;
        unsigned int y = sizeImagen.y;


        texture = sfTexture_createFromImage(imagenFile,NULL);
        sprite = sfSprite_create();
        sfSprite_setTexture(sprite, texture, sfTrue);

        //Guardamos la imagen.
        sfRenderTexture *RenderGuardado = sfRenderTexture_create(x,y,sfFalse);
        sfRenderTexture_drawSprite(RenderGuardado, sprite, NULL);
        sfRenderTexture_drawText(RenderGuardado, texto1, NULL);
        sfRenderTexture_drawText(RenderGuardado, texto2, NULL);
        const sfTexture *TexturaGuardada = sfRenderTexture_getTexture(RenderGuardado);
        sfImage *imagenGuardado = sfImage_create(300,300);
        imagenGuardado = sfTexture_copyToImage(TexturaGuardada);
        sfImage_flipVertically(imagenGuardado);
        sfImage_saveToFile(imagenGuardado,ruta);



    }
    else{
        //0 Representa que esa imagen no esta permitida, por lo cual pasamos al resize.

        //Hacemos un resize.
        sfSprite* spriteResized = Resize(imagenFile);
        sfFloatRect sizeImagenResized = sfSprite_getGlobalBounds(spriteResized);

        int dimensionX = (int)sizeImagenResized.width;
        int dimensionY = (int)sizeImagenResized.height;

        printf("Dimension X: %i, Dimension Y: %i",dimensionX, dimensionY);

        //Guardamos la imagen
        sfRenderTexture *RenderGuardado = sfRenderTexture_create(dimensionX,dimensionY,sfFalse);
        sfRenderTexture_drawSprite(RenderGuardado, spriteResized, NULL);
        sfRenderTexture_drawText(RenderGuardado, texto1, NULL);
        sfRenderTexture_drawText(RenderGuardado, texto2, NULL);
        const sfTexture *TexturaGuardada = sfRenderTexture_getTexture(RenderGuardado);
        sfImage *imagenGuardado = sfImage_create(300,300);
        imagenGuardado = sfTexture_copyToImage(TexturaGuardada);
        sfImage_flipVertically(imagenGuardado);
        sfImage_saveToFile(imagenGuardado,ruta);
    }
}



int main() {
    sfImage* imagen1 = obtenerImagen("C:\\Users\\ExtremeTech\\CLionProjects\\Proyecto#1\\ImagenesDisponibles\\imagen1.jpg");
    sfText * texto1 = obtenerTexto("Memingo",4,1,1, 4, imagen1);
    sfText * texto2 = obtenerTexto("Fino",4,1,3, 4, imagen1);
    guardarImagen(imagen1,texto1,texto2,"C:\\Users\\ExtremeTech\\Desktop\\prueba1.jpg");

    sfImage* imagen2 = obtenerImagen("C:\\Users\\ExtremeTech\\CLionProjects\\Proyecto#1\\ImagenesDisponibles\\imagen2.jpg");
    sfText * texto3 = obtenerTexto("El",4,1,1, 4, imagen2);
    sfText * texto4 = obtenerTexto("Carro",4,1,3, 4, imagen2);
    guardarImagen(imagen2,texto3,texto4,"C:\\Users\\ExtremeTech\\Desktop\\prueba2.jpg");


    sfImage* imagen3 = obtenerImagen("C:\\Users\\ExtremeTech\\CLionProjects\\Proyecto#1\\ImagenesDisponibles\\imagen3.jpg");
    sfText * texto5 = obtenerTexto("Universo",4,2,1, 1, imagen3);
    sfText * texto6 = obtenerTexto("Asombroso",4,2,3, 1, imagen3);
    guardarImagen(imagen3,texto5,texto6,"C:\\Users\\ExtremeTech\\Desktop\\prueba3.jpg");

    return 0;
}