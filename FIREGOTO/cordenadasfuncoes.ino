void Azalt2Radec(double latitude, double longitude, double az, double el, double *ra, double *dec, double horaSiderallocal) {
  double slat = sin(DegreestoRadians (latitude));
  double clat = cos(DegreestoRadians (latitude));
  double saz = sin(DegreestoRadians (az));
  double caz = cos(DegreestoRadians (az));
  double sel = sin(DegreestoRadians (el));
  double cel = cos(DegreestoRadians (el));
  *dec = asin( slat * sel + clat * cel * caz ); // in degrees
  *dec = RadianstoDegrees(*dec);
  double sdec = sin(DegreestoRadians (*dec));
  double cdec = cos(DegreestoRadians (*dec));
  double ha = atan2( -saz * cel , - slat * caz * cel + sel * clat);

  double LHA = atan2(-saz * cel / cdec, (sel - sdec * slat) / (cdec * clat)) * (180 / PI);
  double x = horaSiderallocal - LHA;
  //mod(x,y)= x-x*int(x/y)
  //RA = mod(ThetaLST-LHA,360);
  *ra = x - x * (int)(x / 360);
  if (*ra < 0) {
    *ra = *ra + 360;
  }




}




void Radec2Azalt(double horasiderallocal, double latitude, double ra, double dec, double *az, double *alt)
{
  double tau = horasiderallocal - ra;
  double beta = DegreestoRadians (latitude);
  double delta = DegreestoRadians (dec);
  tau = DegreestoRadians (tau);
  *alt = asin(sin(beta) * sin(delta) + cos(beta) * cos(delta) * cos(tau));
  *az = atan2(- sin(tau) , (cos(beta) * tan(delta) - sin(beta) * cos(tau)));
  *alt =  RadianstoDegrees (*alt);
  *az =  RadianstoDegrees (*az);
  if (*az < 0.0)  *az = *az + 360.0;
  if (*az > 0.0)  *az = *az;
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
  fractime = millis() % 1000;
  return (h + (mins / 60.0) + (ss / 60.0 / 60.0) + fractime/1001);
}



// Convert Degrees, Minutes, Seconds to Decimal Degrees Input -30Ã‚Â°02'53'' - -30, 02, 53
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
  return ((Degrees * M_PI) / 180);
}

// Convert  Radians-Degrees
double RadianstoDegrees (double radian) {
  return ((radian / M_PI) * 180);
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









