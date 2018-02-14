/* version 0.1 du                                                           */
/*  dernière modification :                                                 */
/*         02 06 2015 (SD)                                                  */
/*  auteur :                                                                */
/*         SD Samuel Déom (sdeom@epadesa.fr)                                */

/* Pour fonctionner il faut inclure préalablement les boites à outils :     */
/*   pas de boite                                                           */

/* Liste des routines (en ordre alphabétique)                               */
/*  EstUnType(§texte,§prc_type) Détermine si le texte correspond à un       */
/*      alias de type de données                                            */
/*      Dernière modification : 11/01/2013                                  */

/* Procédures de l'environnement                                            */
proc,EpTypeVide=vide
proc,EpType0=txt
proc,EpType1=entier
proc,EpType4=entier_s
proc,EpType3=reel
proc,EpType2=date
proc,EpType5=bool
proc,EpType6=num
proc,EpType7=alti
proc,EpType8=srid

/*--------------------------------------------------------------------------*/
/*                                ROUTINES                                  */
/*                         par ordre alphabétique                           */
/*--------------------------------------------------------------------------*/

rout,EstUnType(§texte,§prc_type)
/* Détermine si le texte indiqué dans §texte correspond à un alias de type de   */
/*  données                                                                     */
/* Instancie la procédure indiquée dans §prc_type par 1 si vrai, 0 si faux      */
{
  var,§temp_type,§ok,§i
  §temp_type=0 /* Par défaut c'est faux */
  §i=0
  §ok=1
  
  whil,§ok
  {
    §i=[§i+1]
    §ok=[defprc(`EpType[§i]`)]
    if,"§texte==EpType[§i-1]"
    {
      §ok=0
      §temp_type=1
    }
  }
  
  [§prc_type]=[§temp_type]
  
}