# Projet voilier - programmation de µcontrôleur 

Différentes fonctions, reliées à différents périphériques :

<pre>
Vent           →  Girouette           → INPUT  : GPIO + Timer incrémental (quadrature signaux + index)
               →  Voile               → OUTPUT : PWM (timer) Periode 20ms et front montant 1 à 2ms
Gravité        →  Accelerometre       → INPUT  : ADC Tension proportionnelle à l'acceleration (mV/G)
Telecommande   →  RxFM                → INPUT  : PWM (timer) entre 1 et 2ms (1.5ms = neutre)
               →  Plateau             → OUTPUT : GPIO etat bas = droite ; etat haut = gauche
                                                  Timer alpha pour la rapidité [20,100]% 
Pupitre        →  TxFM                → INPUT  : USART 9600 bauds - Data
Alimentation   →  Carte electronique  → OUTPUT : ADC Tension proportionnel valeur de référence
</pre>

Utilisation librairies LL.

Association des PINs aux périphériques :

<pre>
Girouette           → PA.6 =  Timer 3 - Voie 1 
                    → PA.7 =  Timer 3 - Voie 2
                    → PA.5 =  GPIO
                    
Accelerometre       → PC.0 X =  ADC IN 10
                    → PC.1 Y =  ADC IN 11
                    
Alimentation        → PC.2   =  ADC IN 12

Moteur CC           → PA.1   =  Timer 2 - CH2
                    → PA.2   =  GPIO

Servo Voile         → PA.8    = Timer 1 - CH1
                      ou PB.8 = Timer 4 - CH3

RxFM                → PB.6 et PB.7 = Timer 4 - CH1 et CH2

TxFM                → PA.9 = UART 1
                    → PA.11 = GPIO
</pre>
