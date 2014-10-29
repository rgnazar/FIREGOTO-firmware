/*
* Get a double value from the serial port, and send the '_OK_' ack string.
* The value must conains six decimals, in a string with 9 bytes, including sign and decimal dot.
* Examples: '-0.036526', '+5.238388'
*
* \return double.
*/
String readString; //armazena informaÃ§Ãµes mesmo com acompanhamento ativo
char informacao;
char posicao;

/*
 * Get a int value from the serial port, and send the '_OK_' ack string.
 * Examples: '-00', '+05' or 001 102
 *
 * \return int.
 */

int serialGet04dig() {
  if (readString.length() < 4) {
    if (Serial.available() > 0) {
      char c = Serial.read();
      readString += c;
    }
  }
  if (readString.length() == 4) {
    int r = readString.toInt();
    readString = "";
    return (r);
  } else {
    return (-2);
  }

}

/*
 * Get a int value from the serial port, and send the '_OK_' ack string.
 * Examples: '-00', '+05' or 001 102
 *
 * \return int.
 */

int serialGet03dig() {
  if (readString.length() < 3) {
    if (Serial.available() > 0) {
      char c = Serial.read();
      readString += c;
    }
  }
  if (readString.length() == 3) {
    int r = readString.toInt();
    readString = "";
    return (r);

  } else {
    return (-2);
  }

}

/*
 * Get a int value from the serial port, and send the '_OK_' ack string.
 * Examples: '00', '05'
 * not signal
 *
 * \return int.
 */
int serialGet02dig() {
  if (readString.length() < 2) {
    if (Serial.available() > 0) {
      char c = Serial.read();
      readString += c;
    }
  }
  if (readString.length() == 2) {
    int r = readString.toInt();
    readString = "";
    return (r);
  } else {
    return (-2);
  }
}
/*
 * Get a int value from the serial port, and send the '_OK_' ack string.
 * Examples: '-', '+'
 * not signal
 *
 * \return int 1 ou -1.
 */
int serialGetsignal() {
  if (readString.length() < 1) {
    if (Serial.available() > 0) {
      char c = Serial.read();
      readString += c;
    }
  }
  if (readString.length() == 1) {
    if (readString == "-" || readString == "S" || readString == "s" || readString == "O" || readString == "o") {
      readString = "";
      return (-1);
    } else {
      readString = "";
      return (1);
    };
  } else {
    return (-2);
  }
}


void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year());
  Serial.println();
}

void printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

double modulo(double digits) {
  // utility function for digital clock display: prints preceding colon and leading 0
  if (  digits < 0) {
    digits = digits * (-1);
  }
  return (digits);
}

int LeHHMMSS(int *HH, int *MM, int *SS) //Pede e LÃŠ Hora MM SS
{ char fim = 0;
  if (posicao == 0)
  {
    Serial.println("Insira a cordenada AR do objeto: HH MM SS");
    Serial.print("hora = ");
    posicao = -1;
    return (fim);

  }
  if (informacao == 0) {
    *HH = serialGet02dig();
    if (*HH != -2) {
      posicao = 1;
      informacao = 1;
      Serial.println(*HH);
      return (fim);

    }
  }

  if (posicao == 1)
  {
    Serial.print("minuto = ");
    posicao = -1;
    return (fim);

  }
  if (informacao == 1) {
    *MM = serialGet02dig();
    Serial.print("FIM = "); Serial.println(*MM);

    return (fim);


    if (*MM != -2) {
      posicao = 2;
      informacao = 2;
      Serial.println(*MM);
      return (fim);

    }
  }

  if (posicao == 2)
  {
    Serial.print("segundo = ");
    posicao = -1;
    return (fim);

  }

  if (informacao == 2) {
    *SS = serialGet02dig();
    if (*SS != -2) {
      Serial.println(*SS);
      informacao = 0;
      posicao = 0;
      fim = 1;
      return (fim);
    }
  }
}

int LeGGMMSS(int *GG, int *MM, int *SS) //Pede e LÃŠ Grau MM SS
{
  if (posicao == 0)
  {
    Serial.println("Insira a cordenada AR do objeto: HH MM SS");
    Serial.print("hora = ");
    return (0);
    posicao = -1;
  }
  if (informacao == 0) {
    *GG = serialGet02dig();
    if (*GG != -2) {
      posicao = 1;
      informacao = 1;
      Serial.println(*GG);
    }
  }

  if (posicao == 1)
  {
    Serial.print("minuto = ");
    posicao = -1;
  }
  if (informacao == 1) {
    *MM = serialGet02dig();
    if (*MM != -2) {
      posicao = 2;
      informacao = 2;
      Serial.println(*MM);
    }
  }

  if (posicao == 2)
  {
    Serial.print("segundo = ");
    posicao = -1;
  }
  if (informacao == 2) {
    *SS = serialGet02dig();
    if (*SS != -2) {
      Serial.println(*SS);
      informacao = 0;
      posicao = 0;
      return (1);
    }
  }
}


int LeHHDD(int *HH, int *DD) //Pede e LÃŠ Hora e fraÃ§Ã£o decimal da hora
{
}

int LeGGDD(int *GG, int *DD) //Pede e LÃŠ Grau e fraÃ§Ã£o decimal de Grau
{
}


int LeGGDD(int *DD, int *MM, int *AAAA) //Pede e LÃŠ Grau e fraÃ§Ã£o decimal de Grau
{
  if (posicao == 0)
  {
    Serial.println("Insira a dia: DD MM AAAA");
    Serial.print("DIa = (DD)");
    posicao = -1;
  }
  if (informacao == 0) {
    *DD = serialGet02dig();
    if (*DD != -2) {
      posicao = 1;
      informacao = 1;
      Serial.println( *DD);
    }
  }
  if (posicao == 1)
  {
    Serial.print("Mes = (MM)");
    posicao = -1;
  }
  if (informacao == 1) {
    *MM = serialGet02dig();
    if (*MM != -2) {
      posicao = 2;
      informacao = 2;
      Serial.println(*MM);
    }
  }
  if (posicao == 2)
  {
    Serial.print("Ano = (AAAA)");
    posicao = -1;
  }
  if (informacao == 2) {
    *AAAA = serialGet04dig();
    if (*AAAA != -2) {
      posicao = 0;
      informacao = 0;
      Serial.println( *AAAA);
      return (1);
    }
  }
}
int LeSinal()
{
  int sinal = -2;
  if (posicao == 0)
  {
    Serial.println("Insira o hemisferio");
    Serial.print("(N/S ou +/-)");
    posicao = -1;
  }
  if (informacao == 0) {
    sinal = serialGetsignal();
    if (sinal != -2) {
      posicao = 0;
      informacao = 0;
      return (sinal);

    }
  }
}



