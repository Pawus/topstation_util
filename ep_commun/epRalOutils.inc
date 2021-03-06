/* version 0.1 du                                                           */
/*  derni�re modification :                                                 */
/*         11 01 2013 (SD)                                                  */
/*  auteur :                                                                */
/*         SD Samuel D�om (sdeom@epadesa.fr)                                */
/*         VD Vianney Dugrain (vdugrain@epadesa.fr)                         */

/* Pour fonctionner il faut inclure pr�alablement les boites � outils :     */
/*  epTexteOutils                                                           */
/*  epNumOutils                                                             */
/*  epTypeOutils                                                            */

/* Liste des routines                                                       */
/*  DetInd(�mat,�type,�prc_ind)D�termine le premier indice libre d'une      */
/*      rallonge                                                            */
/*      Derni�re modification : 14/12/2012                                  */
/*  EcritRal(�prc_cont,�cmp,�rali,�attr,�type) Enregistre une valeur        */
/*      autre que du texte dans une rallonge                                */
/*      Derni�re modification : 01/10/2013                                  */
/*  rout,EcritContRal(�prc_cont,�cmp,�rali,�attr) Enregistre dans un        */
/*      attribut d'une rallonge un texte de mani�re � ce que la rallonge ne */
/*      d�passe pas 160 caract�res                                          */

/*--------------------------------------------------------------------------*/
/*                                ROUTINES                                  */
/*                         par ordre alphab�tique                           */
/*--------------------------------------------------------------------------*/

rout,DetInd(�mat,�type,�prc_ind)
/* D�termine pour le composant dont le matricule est indiqu� dans �mat,         */
/*  le premier indice libre pour la rallonge indiqu� dans �type                 */
/* L'indice en renvoy� dans la proc�dure dont le nom est indiqu� dans �prc_ind  */
{
  var,�i,�bool
  �i=0
  �bool=1
  whil,�bool
  {
    �bool=[[�mat]&[�type][�i]:><``]
    if,�bool
    {
      �i=[�i+1]
    }
  }
  [�prc_ind]=[�i]
}

rout,EcritRal(�prc_cont,�cmp,�rali,�attr,�type)
/* Enregistre dans l'attribut dont le nom est indiqu� dans �attr de la rallonge */
/*  donn�e dans �rali du composant sp�cifi� dans �cmp le texte contenu dans la  */
/*  proc�dure dont le nom est donn� par �prc_cont de mani�re � ce que la         */
/*  rallonge ne d�passe pas 160 caract�res                                        */
/* Par d�faut le texte est ajout� directement dans la rallonge                  */
{
  var,�contenu,�ok,�typeR,�i
  
  �i=0
  �typeR=0
  �ok=1
  whil,�ok
  {
    �i=[�i+1]
    �ok=[defprc(`EpType[�i]`)]
    if,"�type==EpType[�i-1]"
    {
      �ok=0
      �typeR=[�i-1]
    }
  }
  
  run,EcritRal[�typeR]
  
  rout,EcritRal0
  {
    run,EcritTxtRal([�prc_cont],[�cmp],[�rali],[�attr])
  }
  
  rout,EcritRal1
  {
    var,�temp
    run,FormateEntier([�prc_cont],�temp)
    run,EcritContRal([�temp],[�cmp],[�rali],[�attr])
  }
  
  rout,EcritRal2
  {
    run,EcritContRal([�prc_cont],[�cmp],[�rali],[�attr])
  }
  
  rout,EcritRal3
  {
    run,EcritContRal([�prc_cont],[�cmp],[�rali],[�attr])
  }
  
  rout,EcritRal4
  {
    run,EcritContRal[�prc_cont],[�cmp],[�rali],[�attr])
  }
  
  rout,EcritRal5
  {
    run,EcritContRal([�prc_cont],[�cmp],[�rali],[�attr])
  }
  
  rout,EcritRal6
  {
    run,EcritContRal([�prc_cont],[�cmp],[�rali],[�attr])
  }
  
  rout,EcritRal7
  {
    run,EcritContRal([�prc_cont],[�cmp],[�rali],[�attr])
  }
  
  rout,EcritRal8
  {
    run,EcritContRal([�prc_cont],[�cmp],[�rali],[�attr])
  }
  
}

rout,EcritContRal(�prc_cont,�cmp,�rali,�attr)
/* Enregistre dans l'attribut dont le nom est indiqu� dans �attr de la rallonge */
/*  donn�e dans �ral du composant sp�cifi� dans �cmp le texte contenu dans la   */
/*  proc�dure dont le nom est donn� par �txt de mani�re � ce que la rallonge ne */
/*  d�passe pas 160 caract�res                                                    */
/* Par d�faut le texte est ajout� directement dans la rallonge                  */
{
  var,�rala,�lmax,�lattr,�ral,�ind,�contenu
  /*    Mise � z�ro de l'attribut de la rallonge        */

  if,"len(�rali)=1"
  {
    run,DetInd([�cmp],[�rali],�ind)
    �ral=[�rali][�ind]
  }
  else
  {
    if,"len(�rali)=0"
    {
      run,DetInd([�cmp],V,�ind)
      �ral=V[�ind]
    }
    else
    {
      �ral=[�rali]
    }
  }
  
  if,"len(�attr)=0"
  {
    [�cmp]&[�ral]:
    �lattr=0
  }
  else
  {
    ral,[�cmp]&[�ral]:[�attr]=
    /*    Calcul de la longueur du nom de l'attribut                    */
    /*       -  2        ',' + '='                                        */
    /*       - longueur du nom de l'attribut                            */
    �lattr=[2+len(�attr)]
  }
  �rala=[[�cmp]&[�ral]:]
  /*    Calcul de la longueur de l'attribut � ajouter :                */
  /*        = 159 - longueur du nom de l'attribut                    */
  /*              - longueur de la rallonge existante                */        
  �lmax=[159-len(�rala)-[�lattr]]
  �contenu=[xtr([�prc_cont],0,[�lmax])]
  if,"len(�attr)=0"
  {
    [�cmp]&[�ral]:[�contenu]
  }
  else
  {
    ral,[�cmp]&[�ral]:[�attr]=[�contenu]
  }
}