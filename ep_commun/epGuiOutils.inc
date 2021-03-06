/* version 0.2 du                                                         */
/*  derni�re modification :                                               */
/*         16 09 2013 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel D�om (sdeom@epadesa.fr)                              */

/* Pour fonctionner il faut inclure pr�alablement la boite � outils       */
/*  epListeOutils                                                         */

/* Liste des routines (en ordre alphab�tique)                             */
/*  QAOlstCMP(�nom_liste) Rempli les textes d'un controles de menu        */
/*         d�roulant � partir d'un composant liste                        */
/*         derni�re modification : 16 09 2013 (SD)                        */
/*  QMODlstET(�nom_ctrl,�nom_liste,�nom_prc) Instancie la propri�t� ET    */
/*         d'un contr�le en fonction du rang d'une valeur � chercher dans */
/*         une liste                                                      */
/*         derni�re modification : 27 11 2012 (SD)                        */


rout,QAOlstCMP(�nom_liste)
/* Permet de remplir les textes de contr�le de type CB, OP etc. � partir  */
/*  d'un composant liste (epL) dont le nom est pass� dans la proc�dure    */
/*  �nom_liste. La routine ajoute dans le contr�le chacune des �tiquettes */
/*  (contenues dans les rallonges Q)                                      */
{
  var,�liste
  
  run,SELcmpLST([�nom_liste],�liste) /* selection du bon composant liste et stockage dans la proc�dure �liste */
  if,"�liste><`vide`"
  {
  runr,comp=[�liste],type=V
    {
      qao,et=[ii],tx=[[mm]&Q[ii]:]
    }
  }
}


rout,QMODlstET(�nom_ctrl,�nom_liste,�nom_prc)
/* Permet d'instancier la propri�t� ET d'un controle dont l'identifiant   */
/*  est �nom_ctrl                                                         */
/*  avec le rang de la derni�re ligne dont la valeur (rallonge V) est     */
/*  �gale � la valeur de la proc�dure dont le nom est pass� dans �nom_prc */
/*  de la liste dont le nom est pass� dans la variable �nom_liste         */
/*  si la valeur n'apparait pas, ET est instanci� � 0                     */
{
  var,�et,�liste
  �et=0
  
  run,SELcmpLST([�nom_liste],�liste) /* selection du bon composant liste et stockage dans le composant �liste */
  
  if,"�liste><`vide`"
  {
    runr,comp=[�liste],type=V
    {
      if,"[mm]&V[ii]:==[�nom_prc]"
      {
        �et=[ii]
        [fi]
      }
    }
  }
  QMOD,ID=[�nom_ctrl],ET=[�et]
}