/* version 0.1 du                                                           */
/*  derni�re modification :                                                 */
/*         02 06 2015 (SD)                                                  */
/*  auteur :                                                                */
/*         SD Samuel D�om (sdeom@epadesa.fr)                                */

/* Pour fonctionner il faut inclure pr�alablement les boites � outils :     */
/*   pas de boite                                                           */

/* Liste des routines (en ordre alphab�tique)                               */
/*  EstUnType(�texte,�prc_type) D�termine si le texte correspond � un       */
/*      alias de type de donn�es                                            */
/*      Derni�re modification : 11/01/2013                                  */

/* Proc�dures de l'environnement                                            */
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
/*                         par ordre alphab�tique                           */
/*--------------------------------------------------------------------------*/

rout,EstUnType(�texte,�prc_type)
/* D�termine si le texte indiqu� dans �texte correspond � un alias de type de   */
/*  donn�es                                                                     */
/* Instancie la proc�dure indiqu�e dans �prc_type par 1 si vrai, 0 si faux      */
{
  var,�temp_type,�ok,�i
  �temp_type=0 /* Par d�faut c'est faux */
  �i=0
  �ok=1
  
  whil,�ok
  {
    �i=[�i+1]
    �ok=[defprc(`EpType[�i]`)]
    if,"�texte==EpType[�i-1]"
    {
      �ok=0
      �temp_type=1
    }
  }
  
  [�prc_type]=[�temp_type]
  
}