/* version 0.1 du                                                           */
/*  dernière modification :                                                 */
/*         11 01 2013 (SD)                                                  */
/*  auteur :                                                                */
/*         SD Samuel Déom (sdeom@epadesa.fr)                                */
/*         VD Vianney Dugrain (vdugrain@epadesa.fr)                         */

/* Pour fonctionner il faut inclure préalablement les boites à outils :     */
/*  epTexteOutils                                                           */
/*  epNumOutils                                                             */
/*  epTypeOutils                                                            */

/* Liste des routines                                                       */
/*  DetInd(§mat,§type,§prc_ind)Détermine le premier indice libre d'une      */
/*      rallonge                                                            */
/*      Dernière modification : 14/12/2012                                  */
/*  EcritRal(§prc_cont,§cmp,§rali,§attr,§type) Enregistre une valeur        */
/*      autre que du texte dans une rallonge                                */
/*      Dernière modification : 01/10/2013                                  */

/*--------------------------------------------------------------------------*/
/*                                ROUTINES                                  */
/*                         par ordre alphabétique                           */
/*--------------------------------------------------------------------------*/

rout,DetInd(§mat,§type,§prc_ind)
/* Détermine pour le composant dont le matricule est indiqué dans §mat,         */
/*  le premier indice libre pour la rallonge indiqué dans §type                 */
/* L'indice en renvoyé dans la procédure dont le nom est indiqué dans §prc_ind  */
{
  var,§i,§bool
  §i=0
  §bool=1
  whil,§bool
  {
    §bool=[[§mat]&[§type][§i]:><``]
    if,§bool
    {
      §i=[§i+1]
    }
  }
  [§prc_ind]=[§i]
}

rout,EcritRal(§prc_cont,§cmp,§rali,§attr,§type)
/* Enregistre dans l'attribut dont le nom est indiqué dans §attr de la rallonge */
/*  donnée dans §rali du composant spécifié dans §cmp le texte contenu dans la  */
/*  procédure dont le nom est donné par §prc_cont de manière à ce que la         */
/*  rallonge ne dépasse pas 160 caractères                                        */
/* Par défaut le texte est ajouté directement dans la rallonge                  */
{
  var,§contenu,§ok,§typeR,§i
  
  §i=0
  §typeR=0
  §ok=1
  whil,§ok
  {
    §i=[§i+1]
    §ok=[defprc(`EpType[§i]`)]
    if,"§type==EpType[§i-1]"
    {
      §ok=0
      §typeR=[§i-1]
    }
  }
  
  run,EcritRal[§typeR]
  
  rout,EcritRal0
  {
    run,EcritTxtRal([§prc_cont],[§cmp],[§rali],[§attr])
  }
  
  rout,EcritRal1
  {
    var,§temp
    run,FormateEntier([§prc_cont],§temp)
    run,EcritContRal([§temp],[§cmp],[§rali],[§attr])
  }
  
  rout,EcritRal2
  {
    run,EcritContRal([§prc_cont],[§cmp],[§rali],[§attr])
  }
  
  rout,EcritRal3
  {
    run,EcritContRal([§prc_cont],[§cmp],[§rali],[§attr])
  }
  
  rout,EcritRal4
  {
    run,EcritContRal[§prc_cont],[§cmp],[§rali],[§attr])
  }
  
  rout,EcritRal5
  {
    run,EcritContRal([§prc_cont],[§cmp],[§rali],[§attr])
  }
  
  rout,EcritRal6
  {
    run,EcritContRal([§prc_cont],[§cmp],[§rali],[§attr])
  }
  
  rout,EcritRal7
  {
    run,EcritContRal([§prc_cont],[§cmp],[§rali],[§attr])
  }
  
  rout,EcritRal8
  {
    run,EcritContRal([§prc_cont],[§cmp],[§rali],[§attr])
  }
  
}

rout,EcritContRal(§prc_cont,§cmp,§rali,§attr)
/* Enregistre dans l'attribut dont le nom est indiqué dans §attr de la rallonge */
/*  donnée dans §ral du composant spécifié dans §cmp le texte contenu dans la   */
/*  procédure dont le nom est donné par §txt de manière à ce que la rallonge ne */
/*  dépasse pas 160 caractères                                                    */
/* Par défaut le texte est ajouté directement dans la rallonge                  */
{
  var,§rala,§lmax,§lattr,§ral,§ind,§contenu
  /*    Mise à zéro de l'attribut de la rallonge        */

  if,"len(§rali)=1"
  {
    run,DetInd([§cmp],[§rali],§ind)
    §ral=[§rali][§ind]
  }
  else
  {
    if,"len(§rali)=0"
    {
      run,DetInd([§cmp],V,§ind)
      §ral=V[§ind]
    }
    else
    {
      §ral=[§rali]
    }
  }
  
  if,"len(§attr)=0"
  {
    [§cmp]&[§ral]:
    §lattr=0
  }
  else
  {
    ral,[§cmp]&[§ral]:[§attr]=
    /*    Calcul de la longueur du nom de l'attribut                    */
    /*       -  2        ',' + '='                                        */
    /*       - longueur du nom de l'attribut                            */
    §lattr=[2+len(§attr)]
  }
  §rala=[[§cmp]&[§ral]:]
  /*    Calcul de la longueur de l'attribut à ajouter :                */
  /*        = 159 - longueur du nom de l'attribut                    */
  /*              - longueur de la rallonge existante                */        
  §lmax=[159-len(§rala)-[§lattr]]
  §contenu=[xtr([§prc_cont],0,[§lmax])]
  if,"len(§attr)=0"
  {
    [§cmp]&[§ral]:[§contenu]
  }
  else
  {
    ral,[§cmp]&[§ral]:[§attr]=[§contenu]
  }
}