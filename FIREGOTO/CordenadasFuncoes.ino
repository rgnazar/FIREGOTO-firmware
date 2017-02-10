void Azalt2Radec(double latitude, double longitude, double az, double el, double *ra, double *dec, double horaSiderallocal) {
  double slat = sin(DegreestoRadians (latitude));
  double clat = cos(DegreestoRadians (latitude));
  double saz = sin(DegreestoRadians (az));
  double caz = cos(DegreestoRadians (az));
  double sel = sin(DegreestoRadians (el));
  double cel = cos(DegreestoRadians (el));
  //  *dec = asin( slat * sel + clat * cel * caz ); // in degrees
  
  //  *dec = RadianstoDegrees(*dec);
  *dec = asin((sin(DegreestoRadians (latitude)) * sin(DegreestoRadians (el))) - (cos(DegreestoRadians (latitude)) * cos(DegreestoRadians (el)) * cos(DegreestoRadians (az) + PI)));
  *dec = *dec * 180 / PI;
  double sdec = sin(DegreestoRadians (*dec));
  double cdec = cos(DegreestoRadians (*dec));
  // double LHA = atan2(-saz * cel / cdec, (sel - sdec * slat) / (cdec * clat)) ;

  double LHA = atan2(sin(DegreestoRadians (az) + PI), cos(DegreestoRadians (az) + PI) * sin(DegreestoRadians (latitude)) + tan(DegreestoRadians (el)) * cos(DegreestoRadians (latitude)));
  LHA = LHA * 180 / PI;
  double x = horaSiderallocal - LHA;

  //mod(x,y)= x-x*int(x/y)
  //RA = mod(ThetaLST-LHA,360);
  *ra = x - x * (int)(x / 360);

  while (*ra < 0.0)
    *ra = *ra + 360.0;
  while (*ra > 360.0)
    *ra = *ra - 360.0;


  /*   LHA = Atan2(Sin(Az + PI), Cos(Az + PI) * Sin(Lat) + Tan(Alt) * Cos(Lat));
           Angle DEC = Asin(Sin(Location.Lat) * Sin(AzAlt.Alt) - Cos(Location.Lat) * Cos(AzAlt.Alt) * Cos(AzAlt.Az + PI));
           Angle RA = LST - HA;
           return new CroodRaDec(RA, DEC);*/

}




void Radec2Azalt(double horasiderallocal, double latitude, double ra, double dec, double *az, double *alt)
{
  double tau = horasiderallocal - ra;
  double beta = DegreestoRadians (latitude);
  double delta = DegreestoRadians (dec);
  tau = DegreestoRadians (tau);
  /*  *alt = asin(sin(beta) * sin(delta) + cos(beta) * cos(delta) * cos(tau));
    *az = atan2(- sin(tau) , (cos(beta) * tan(delta) - sin(beta) * cos(tau)));
*/
  double Ha = DegreestoRadians (horasiderallocal - ra);
  *az = atan2(sin(Ha), cos(Ha) * sin(DegreestoRadians (latitude)) - tan(DegreestoRadians (dec)) * cos(DegreestoRadians (latitude)));
  *az = *az + PI;
  *alt = asin(sin(DegreestoRadians (latitude)) * sin(DegreestoRadians (dec))  + cos(DegreestoRadians (latitude)) * cos(DegreestoRadians (dec)) * cos(Ha));

    *alt =  RadianstoDegrees (*alt);
    *az =  RadianstoDegrees (*az);
  while (*az < 0.0)
    *az = *az + 360.0;
  while (*az > 360.0)
    *az = *az - 360.0;

  /*          Angle Ha = LST - RaDec.Ra;

              double Az = Math.Atan2(Math.Sin(Ha), Math.Cos(Ha) * Math.Sin(Location.Lat) - Math.Tan(RaDec.Dec) * Math.Cos(Location.Lat));
              double Alt = Math.Asin(Math.Sin(Location.Lat) * Math.Sin(RaDec.Dec)  + Math.Cos(Location.Lat) * Math.Cos(RaDec.Dec) * Math.Cos(Ha));

              return new CroodAzAlt(Az + Math.PI, Alt);*/

}


//calcula a hora sideral local Longitude e HoraSideral
double HoraSiderallocal(double lon, double horasideral) {
  return (horasideral + lon);
}


//calcula a hora sideral jd = juliano day
double HoraSideral(double jd) {
  double t = jd / 36525.0;
  double theta0 = 280.46061837 + 0.98564736629 * jd + 360.0 * (jd - floor(jd)) + 0.000387933 * t * t - t * t * t / 38710000.0;
  while (theta0 < 0.0)
    theta0 = theta0 + 360.0;
  while (theta0 > 360.0)
    theta0 = theta0 - 360.0;
  return theta0;
}


//Encontra o JulianoDay  decH = hora em decimal ex 12.873
double JulianoDay (double y, double m, double d, double decH) {
  return ( 367 * y - floor(7 * (y + floor( (m + 9) / 12)) / 4) + floor(275 * m / 9) + d - 730531.5 + decH / 24);
}


//converte Hora em HoraDecimal
double  Hora2DecHora(double h, double mins, double ss) {
  return (h + (mins / 60.0) + (ss / 60.0 / 60.0));
}



// Convert Degrees, Minutes, Seconds to Decimal Degrees Input -30Ãƒâ€šÃ‚Â°02'53'' - -30, 02, 53
double DegMinSec2DecDeg(double GG, double MM, double SS) {
  if (GG < 0) {
    MM = 0 - MM;
    SS = 0 - SS;
  }
  return (GG + (MM / 60) + (SS / (60 * 60)));
}

// Convert Decimal Degrees to Degrees, Minutes, Seconds return Deg
int DecDegtoDeg(double DecDeg) {
  double deg = (int)DecDeg;
  double minsss = ((DecDeg - deg) * 60);
  double mins = (int)(minsss);
  double secs = ((minsss - mins) * 60 );
  return ((int) deg);
}
// Convert Decimal Degrees to Degrees, Minutes, Seconds return Min
int DecDegtoMin(double DecDeg) {
  double deg = (int)DecDeg;
  double minsss = ((DecDeg - deg) * 60);
  double mins = (int)(minsss);
  double secs = ((minsss - mins) * 60 );
  if (deg < 0) {
    mins = mins * (-1);
  };
  return ((int)mins);
}
// Convert Decimal Degrees to Degrees, Minutes, Seconds return Sec
int DecDegtoSec(double DecDeg) {
  double deg = (int)DecDeg;
  double minsss = ((DecDeg - deg) * 60);
  double mins = (int)(minsss);
  double secs = ((minsss - mins) * 60 );
  if (deg < 0) {
    secs = secs * (-1);
  };
  return ((int)secs);
}

// Convert  Degrees-Radians
double DegreestoRadians (double Degrees) {
  return ((Degrees * PI) / 180);
}

// Convert  Radians-Degrees
double RadianstoDegrees (double radian) {
  return ((radian / PI) * 180);
}

// Convert  hours-DecDegrees
double Hours2DecDegrees(int HH, int MM, int SS) {
  double HHH = ((double)HH + ((double)MM / 60) + ((double)SS / (60 * 60)));
  HHH = 15 * HHH ;
  return (HHH);
}

// Convert  Degrees-hours
// Convert Decimal Degrees to hours, Minutes, Seconds return HH
int DecDeg2HoursHH(double hDecDeg) {
  hDecDeg = (hDecDeg / 15);
  double hh = (int)hDecDeg;
  double minsss = ((hDecDeg - hh) * 60);
  double mins = (int)(minsss);
  double secs = ((minsss - mins) * 60 );
  return ((int)hh);
}

// Convert Decimal Degrees to hours, Minutes, Seconds return Min
int DecDeg2HoursMM(double hDecDeg) {
  hDecDeg = (hDecDeg / 15);
  double hh = (int)hDecDeg;
  double minsss = ((hDecDeg - hh) * 60);
  double mins = (int)(minsss);
  double secs = ((minsss - mins) * 60 );
  return ((int)mins);
}

// Convert Decimal Degrees to hours, Minutes, Seconds return Sec
int DecDeg2HoursSEC(double hDecDeg) {
  hDecDeg = (hDecDeg / 15);
  double hh = (int)hDecDeg;
  double minsss = ((hDecDeg - hh) * 60);
  double mins = (int)(minsss);
  double secs = ((minsss - mins) * 60 );
  return ((int)secs);

}


// Convert  HoursDecimal
// Convert Decimal Hour to hours, Minutes, Seconds return HH
int DecHour2HoursHH(double hDecHour) {
  double hh = (int)hDecHour;
  double minsss = ((hDecHour - hh) * 60);
  double mins = (int)(minsss);
  double secs = ((minsss - mins) * 60 );
  return ((int)hh);
}

// Convert Decimal Hour to hours, Minutes, Seconds return Min
int DecHour2HoursMM(double hDecHour) {
  double hh = (int)hDecHour;
  double minsss = ((hDecHour - hh) * 60);
  double mins = (int)(minsss);
  double secs = ((minsss - mins) * 60 );
  return ((int)mins);
}

// Convert Decimal Hour to hours, Minutes, Seconds return Sec
int DecHour2HoursSEC(double hDecHour) {
  double hh = (int)hDecHour;
  double minsss = ((hDecHour - hh) * 60);
  double mins = (int)(minsss);
  double secs = ((minsss - mins) * 60 );
  return ((int)secs);

}










