FIREGOTO
Arduino e Montagem Dobson Caseira com GOTO

http://www.astronomoamador.com.br/arduino-controle-de-telescopio

GRUPO
https://groups.google.com/forum/#!forum/firegoto

Faça você mesmo!!!

Se é adepto ao faça você mesmo;

Gosta de aprendizagem multidisciplinar;

E é curioso;
E gosta de Astronomia e Observação....

O Projeto.
    
Depois que fiz a manutenção em uma base Orion Dob GOTO resolvi fazer um projeto open (livre) para automatizar telescopios em bases dobsonianas.

Caracteristicas deste projeto:
1 - Pouca solda;

2 - Controle do telescópio deve ser livre de PC;

3 - Usar motor de passo de baixo custo;

4 - Usar engrenagens e redução de baixo custo;

5 - Pouco ou nenhum serviço de torno;

6 - Pode usar varias tipos de fontes incluindo as de notebook (12volts a 30 volts);

7 - Aceitar  100% do protocolo LX200;

8 - Melhorar o uso com  ASCOM;

A Ideia é a movimentação dos eixos em montagem Dobson usando materiais de fácil acesso no mercado nacional fazendo usod o protocolo de comunicação LX200, controlado pela plataforma Arduino Due com código de programação aberto;

Vale Apena $$$$$$$ FINANCEIRAMENTE
Não,

                            Sim, 

                                                        Talvez

E for considerar unicamente financeiro, não vale apena.

Mas se for por curiosidade e interesse em aprender..... SIM

Talvez um industrial barato será melhor que um montado pelo mesmo preço. Agora se quiser algo de muito boa qualidade Industrial, o de muita boa qualidade ATM será mais barato.

Outros projetos que vale apena conhecer RECOMENTO CONHECER e foram fontes de inspiração e (copiação)

http://soundstepper.sourceforge.net/

Maciel Bassani Sparrenberger

https://sites.google.com/site/picgoto/

Marcos Baungartner

http://www.stellarjourney.com/

Howard Dutton

Eletrônica necessária:
1 - Arduino Due (32 bits);
2 - 02 driver DRV8825

3 - Modulo Bluetooth JY-MCU

4 - Transformador DC-DC

5 - Motores de Passo BIPOLAR (4 ou 8 fios)


O que é Arduino
Arduino é uma plataforma eletrônica de código aberto. Com hardware e software de fácil utilização. É destinado para todas as pessoa que desejam fazer projetos eletrônicos.

https://www.arduino.cc/

Característica dos Arduino

Hardware livre, projeto livre, qualquer um pode clonar as placas mas não podem clonar o nome.

Programação baseado na linguagem C++ e JAVA, Fácil de aprender.

Não há restrição na comercialização de projetos baseado em Arduino.

Usa arquitetura ARM de processador

Baixo custo

Arduino DUE
Microcontroller AT91SAM3X8E

A 32-bit core, that allows operations on 4 bytes wide data within a Single CPU clock. (for more information look int type page).

CPU Clock at 84Mhz.

512 KBytes of Flash memory for code.

DMA controller, that can relieve the CPU from doing memory intensive tasks.

54 pin I/O (of which 12 provide PWM output)

04 Port Serial e 2 Port USB

A base é o Arduino Due (32 bits) nele que receberá a programação e é nele que controla os demais componentes. Os 02 driver DRV8825 serve para receber o sinal de baixa potencia do ARDUINO e mandar em alta potencia para os motores de passo, os drivers esta também gerencia o controle PWM das bobinas nos motores.


A conexão entre PC ou Tablet (SmartFone) na Montagem pode ser feitas de duas formas ou usando um cabo USB ou via bluetooth. O Modulo Bluetooth JY-MCU de 3.3v importante 3.3v sendo este último acho mais fácil de usar.



Para evitar a necessidade de varias fontes, eu recomendo o uso de um transformador DC-DC com ele podemos usar uma fonte de 12v a 24 volts e transformar entregar 10 volts para o Arduino sem risco de queimá-lo.




Sobre os Motores de Passo tem que ser BIPOLAR 4 ou 8 fios. UNIPOLAR não funciona (5 fios) tenha em mente que quanto o mior numero de passo, menos redução mecanica é necessaria.

Número mágico 24*60*60*15 = 1.296.000

Sua redução total tem que ficar acima de 1.296.000:1 exemplo:

Cj 01 Engrenagens 144:1

Cj 02 Engrenagens 4:1

Motor de 200 Passos

Driver 8825 fornece 32 micropasso

Logo você tem: 200*32*144*4=3.686.400 esta é uma boa redução. Falaremos mais de mecanica lá para frente.....



MÃO NA MASSA


Esquemas eletricos:
Atualmente esta é a placa PCI para o projeto, IMPORTANTE verificar sempre se não tem uma nova versão em github.com .






Protocolo LX200
Padrão de mercado;

Suportado por diversos software como SkySafari (Tablet); Cartes du Ciel; C2A; PHD Guiding.

Muito completo;

Sem reinventar a roda.

http://www.meade.com/support/LX200CommandSet.pdf

Controle - Hand Tablet - Hand PAD

SkySafari- Reinventar a roda;

-Planetário de baixo custo 27 Dólares;



Desenvolvendo próprio;



Videos sobre o projeto.
https://www.youtube.com/watch?v=ZFidbwVeSqo

https://www.youtube.com/watch?v=fCeodEw17WI

https://www.youtube.com/watch?v=YLftPAcaMxI


Os arquivos para o arduino e o Andorid estão em: https://github.com/rgnazar

Driver ASCOM esta em :http://www.stellarjourney.com/index.php?r=site/software_telescope


GNU AFFERO GENERAL PUBLIC LICENSE https://github.com/rgnazar/FIREGOTO-firmware/blob/master/LICENSE.md


https://github.com/juanrmn/Arduino-Telescope-Control/blob/master/main/arduino/plaser/CoordsLib.h
