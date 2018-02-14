/* version 0.2 du                                                         */
/*  dernière modification :                                               */
/*         16 09 2013 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel Déom (sdeom@epadesa.fr)                              */

/* Pour fonctionner il faut inclure préalablement la boite à outils       */
/*  epListeOutils                                                         */

/* Liste des routines (en ordre alphabétique)                             */
/*  QAOlstCMP(§nom_liste) Rempli les textes d'un controles de menu        */
/*         déroulant à partir d'un composant liste                        */
/*         dernière modification : 16 09 2013 (SD)                        */
/*  QMODlstET(§nom_ctrl,§nom_liste,§nom_prc) Instancie la propriété ET    */
/*         d'un contrôle en fonction du rang d'une valeur à chercher dans */
/*         une liste                                                      */
/*         dernière modification : 27 11 2012 (SD)                        */


rout,QAOlstCMP(§nom_liste)
/* Permet de remplir les textes de contrôle de type CB, OP etc. à partir  */
/*  d'un composant liste (epL) dont le nom est passé dans la procédure    */
/*  §nom_liste. La routine ajoute dans le contrôle chacune des étiquettes */
/*  (contenues dans les rallonges Q)                                      */
{
  var,§liste
  
  run,SELcmpLST([§nom_liste],§liste) /* selection du bon composant liste et stockage dans la procédure §liste */
  if,"§liste><`vide`"
  {
  runr,comp=[§liste],type=V
    {
      qao,et=[ii],tx=[[mm]&Q[ii]:]
    }
  }
}


rout,QMODlstET(§nom_ctrl,§nom_liste,§nom_prc)
/* Permet d'instancier la propriété ET d'un controle dont l'identifiant   */
/*  est §nom_ctrl                                                         */
/*  avec le rang de la dernière ligne dont la valeur (rallonge V) est     */
/*  égale à la valeur de la procédure dont le nom est passé dans §nom_prc */
/*  de la liste dont le nom est passé dans la variable §nom_liste         */
/*  si la valeur n'apparait pas, ET est instancié à 0                     */
{
  var,§et,§liste
  §et=0
  
  run,SELcmpLST([§nom_liste],§liste) /* selection du bon composant liste et stockage dans le composant §liste */
  
  if,"§liste><`vide`"
  {
    runr,comp=[§liste],type=V
    {
      if,"[mm]&V[ii]:==[§nom_prc]"
      {
        §et=[ii]
        [fi]
      }
    }
  }
  QMOD,ID=[§nom_ctrl],ET=[§et]
}