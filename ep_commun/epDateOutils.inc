/* version 0.1 du                                                         */
/*  dernière modification :                                               */
/*         16 07 2013 (VD)                                                */
/*  auteur :                                                              */
/*         VD Vianney DUGRAIN (vdugrain@epadesa.fr)                       */

/* Liste des routines                                                     */
/*  DateCourante												          */
/*         renvoie la date courante au format jj/mm/aaaa			      */

rout,DateCourante(§date)
{
  var,§date_brute,§annee
  §date_brute=[date]
  §annee=[xtr(§date_brute,6,2)]
  §annee=20[§annee]
  [§date]=[xtr(§date_brute,0,6)][§annee]
}