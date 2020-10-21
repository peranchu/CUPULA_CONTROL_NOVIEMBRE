//============DECLARACIONES ELEMENTOS PANTALLA================================

//Declaraciones elementos de página 0
NexPage page0 = NexPage(0, 0, "intro");

///////////////////////////////////////////////

//Declaraciones de página 1 MENU
NexPage page1 = NexPage(1, 0, "menu");

//Elementos página 1 MENU
NexButton b0_1 = NexButton(1, 1, "b0menu"); //Botón Ajustes
NexButton b1_1 = NexButton(1, 2, "b1menu"); //Botón Inicio

///////////////// FIN PANTALLA 1 /////////////////////////////

//Declaraciones de página 2 repro
NexPage page2 = NexPage(2, 0, "repro");

//Elementos Pantalla 2 repro

//Botones Reproducción
NexButton b1_2 = NexButton(2, 5, "b1");
NexButton b2_2 = NexButton(2, 6, "b2");
NexButton b3_2 = NexButton(2, 7, "b3");
NexButton b4_2 = NexButton(2, 8, "b4");
NexButton b5_2 = NexButton(2, 9, "b5");
NexButton b6_2 = NexButton(2, 10, "b6");

NexButton b7_2 = NexButton(2, 3, "b7stop"); //Botón STOP

NexSlider h0_2 = NexSlider(2, 2, "h0vol"); //volumen

/////////////// FIN PANTALLA 2 ////////////////////////////

//Declaraciones página 3 micrófono
NexPage page3 = NexPage(3, 0, "microfono");

//Elementos pantalla 3 repro

//////////// FIN PANTALLA 3 ///////////////////////////

//Declaraciones página 4 umbral
NexPage page4 = NexPage(4, 0, "umbral");

//Elementos pçagina 4 umbral
NexSlider h0_4 = NexSlider(4, 5, "h0Umbral"); // Ajuste umbral

//========================== FIN PANTALLA 4 =============================

//==================FIN DECLARACIÓN ELEMENTOS PANTALLA=================================

//Lista de Eventos Pantalla
NexTouch *nex_listen_list[] =
    {
        &page0, //página 0
        &page1, //Página 1
        &b0_1,
        &b1_1,
        &page2, //Página 2
        &b1_2,
        &b2_2,
        &b3_2,
        &b4_2,
        &b5_2,
        &b6_2,
        &b7_2,
        &h0_2,
        &page3, //Página 3
        &page4, //Página 4
        &h0_4,
        NULL};

//=============================FIN LISTA EVENTOS PANTALLA==============================