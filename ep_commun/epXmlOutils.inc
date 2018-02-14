/* version 0.1                                                              */
/*  dernière modification :                                                 */
/*         22 06 2016 (SD)                                                  */
/*  auteur :                                                                */
/*         SD Samuel Déom (sdeom@epadesa.fr)                                */
/*         AR Antoine Rabaud (arabaud@epadesa.fr)                           */

/* Pour fonctionner il faut inclure préalablement les boites à outils :     */
/*   pas de boite                                                           */

/* Liste des routines (en ordre alphabétique)                               */
/*  Comment(§prc_txt,§rg_ident) Ecrit un commentaire                        */
/*      procédure dont le nom est passé dans §prc_txt avec une identation   */
/*      de rang §rg_ident                                                   */
/*    Dernière modification : 22/06/2016 (SD)                               */


/* Procédures de l'environnement                                            */
proc,PrcIdent"Procedure d'identation"=`  `
proc,RadTrad"Radical des composants de traduction"=epXml

/*--------------------------------------------------------------------------*/
/*                                ROUTINES                                  */
/*                         par ordre alphabétique                           */
/*--------------------------------------------------------------------------*/

rout,Comment(§prc_txt,§rg_ident)
{
  var,§texte
  §texte=<!-- [[§prc_txt]] -->
  run,ImprIdent(§texte,[§rg_ident])
}

rout,EcriXml(§prc_sel,§mat_t,§prc_fic,§xlink)
/* Traduit les composants formant la sélection dont le nom est donné dans la    */
/*    procédure contenu dans §prc_sel, conformement au fichier de traduction    */
/*    au format xslt */

{
  var,§commentaire
  list,file=[[§prc_fic]],raz=1
  
  /* Ecriture du prologue : entête, déclaration de type (DTD) et commentaires   */
  impr,<?xml version="1.0" encoding="windows-1252"?>
  
  /* Pas de gestion des DTD pour l'instant */
  
  /* Commentaires éventuels */
  impr,
  §commentaire=Fichier généré de manière automatique à partir de TopStation
  run,Comment(§commentaire,0)
  
  /* On lance l'écriture du corps du document par l'élément racine */
  impr,
  marq,nivo=10,mess=`Lancement de la routine d'export XML`
  run,Comment([§prc_sel],0)
  run,EcriElement([§prc_sel],[§mat_t],[§xlink],0)
  anul,nivo=10
  list
}

rout,ImprIdent(§prc_txt,§rg_ident)
{
  impr,[rpt([PrcIdent],§rg_ident)][[§prc_txt]]
}

rout,EcriElement(§prc_sel,§mat_e,§xlink,§rg_ident)
/* Traduit les composants formant la sélection dont le nom est donné dans la    */
/*    procédure contenu dans §prc_sel, en éléments xml décrit dans le composant */
/*    dont le matricule est donné dans §mat_e                                   */
/*  §xlink indique est un booléen qui indique s'il faut faire usage d'attribut  */
/*    xlink                                                                     */
/*  §rg_ident est en entier naturel qui indique le rang de l'identation         */
{ 
  var,§sel,§mat,§valeur,§ligne
  var,§vide
  /* booleen indiquant si le contenu est vide (valeur 0) */
  var,§simple
  /* booleen indiquant si le contenu est simple (valeur 1) */
  
  if,"[§mat_e]&V0:sel==`!root`"
  /* Choix des constructeurs : la routine initiera la construction d'un élément */
  /*   pour chaque composant appartenant à la sélection [§prc_sel] filtrée par  */
  /*   par la formule de sélection indiquée dans l'attribut &V0:sel du compo-   */
  /*   [§mat]. La formule spéciale !root indique que l'on écrit la racine du    */
  /*   fichier xml, la routine sera initiée sur le seul composant [§mat_e]      */
  {
    §sel={§mat_e}
    /* cas particulier de l'élément racine */
  }
  else
  {
    if,"[§mat_e]&V0:sel><``"
    {
      §sel={{§prc_sel}}*({[§mat_e]&V0:sel})
    }
    else
    {
      §sel={{§prc_sel}}
    }
  }
  
  /* On enregistre les espaces de noms */
  run,EnrgNSpace([§mat_e],[§rg_ident])
  
  /* sauvegarde du qname */
  var,§prefix
  §prefix=[[§mat_e]&T0:prefix]
  if,"§prefix==``"
  {
    run,Prefix([[§mat_e]&T0:uri],[§rg_ident],§prefix)
  }
  if,"§prefix><``"
  {
    [RadTrad].[§rg_ident]&T0:qname=[§prefix]:[[§mat_e]&T0:name]
  }
  else
  {
    [RadTrad].[§rg_ident]&T0:qname=[[§mat_e]&T0:name]
  }
  
  runs,[§sel]
  {
    §mat=[mm]
    
    
    /* On teste si le contenu est vide */
    §vide=1
    if,"[§mat_e]&V1:><``"
    {
      §vide=0
    }
    
    /* On teste si le contenu est simple : c.a.d n'est pas composé d'autre élé- */
    /*  ments */
    §simple=1
    if,"1-§vide"
    {
    if,"[§mat_e]&V1:constructeur><``"
      {
        §simple=0
      }
    }
    
    run,EcriBalise([§mat_e],[§vide],[§simple],[§rg_ident])
    if,"1-§simple"
    {
      runr,[§mat_e],V
      {
        if,"ii>0"
        {
          var,§sel_r,§xlink_r
          §sel_r=[[rr]:sel]
          
          if,"§sel_r==``"
          /* si vide, s'applique sur l'élément lui même */
          {
            §sel_r=[§mat]
            if,"[§mat_e]&V0:sel==`!root`"
            /* cas particulier de l'élément racine, on applique à la sélection d'entrée */
            {
              §sel_r=[[§prc_sel]]
            }
          }
          
          §xlink_r=0
          
          /* on sauve les procédures de la routine */
          [RadTrad].[§rg_ident]&Q0:prc_sel=[§prc_sel] /* sauvegarde du prc_sel */
          [RadTrad].[§rg_ident]&Q1:mat_e=[§mat_e] /* sauvegarde du mat_e */
          [RadTrad].[§rg_ident]&V0:xlink=[§xlink] /* sauvegarde du xlink */
          
          run,EcriElement(§sel_r,[[rr]:constructeur],[§xlink_r],[§rg_ident+1])
          
          /* on rétabli les procédures initiales */
          §rg_ident=[§rg_ident-1]
          §prc_sel=[[RadTrad].[§rg_ident]&Q0:prc_sel]
          §mat_e=[[RadTrad].[§rg_ident]&Q1:mat_e]
          §xlink=[[RadTrad].[§rg_ident]&V0:xlink]
        }
      }

      run,ImprIdent(`</[[RadTrad].[§rg_ident]&T0:qname]>`,[§rg_ident])

    }
    else
    {
      
    }
  }
}

rout,EcriBalise(§mat,§vide,§simple,§rg_ident)
{
  var,§nspace
  /* nombre de déclaration d'espace de nom */
  var,§nattr
  /* nombre d'attribut */
  var,§prc_txtbalise
  
  /* Gestion du nom */
  
  §prc_txtbalise=[[RadTrad].[§rg_ident]&T0:qname]
  
  /* Gestion des attributs particuliers qui sont dans &T0 */
  var,§lang,§space,§base,§id
  §lang=[[§mat]&T0:lang]
  if,"§lang><``"
  {
    §prc_txtbalise=[§prc_txtbalise] xml:lang="{§lang}"
  }
  
  §space=[[§mat]&T0:space]
  if,"§space><``"
  {
    §prc_txtbalise=[§prc_txtbalise] xml:space="{§space}"
  }
  
  §base=[[§mat]&T0:base]
  if,"§base><``"
  {
    §prc_txtbalise=[§prc_txtbalise] xml:base="{§base}"
  }
  
  §id=[[§mat]&T0:id]
  if,"§id><``"
  {
    §prc_txtbalise=[§prc_txtbalise] xml:id="{§id}"
  }
  
  §nspace=0
  runr,comp=[§mat],type=Q
  {
    §nspace=[§nspace+1]
  }
  §nattr=0
  runr,comp=[§mat],type=T
  {
    §nattr=[§nattr+1]
  }
  
  if,"§nspace+§nattr<2"
  {
    if,"§vide"
    {
      run,ImprIdent(`<[§prc_txtbalise]/>`,[§rg_ident])
    }
    else
    {
      if,"§simple"
      {
        run,ImprIdent(`<[§prc_txtbalise]>[[§mat]&V1:]</[[§mat]&T0:name]>`,[§rg_ident])
      }
      else
      {
        run,ImprIdent(`<[§prc_txtbalise]>`,[§rg_ident])
      }
    }
  }
  else
  {
    if,"§vide"
    {
      run,ImprIdent(`<[§prc_txtbalise]`,[§rg_ident])
      run,EcriAttr([§mat],[§rg_ident+1])
      run,EcriNSpace([§mat],[§rg_ident+1])
      run,ImprIdent(`/>`,[§rg_ident])
    }
    else
    {
      if,"§simple"
      {
        run,ImprIdent(`<[§prc_txtbalise]`,[§rg_ident])
        run,EcriAttr([§mat],[§rg_ident+1])
        run,EcriNSpace([§mat],[§rg_ident+1])
        run,ImprIdent(`>[[§mat]&V1:]</[[RadTrad].[§rg_ident]&T0:qname]>`,[§rg_ident])
      }
      else
      {
        run,ImprIdent(`<[§prc_txtbalise]`,[§rg_ident])
        run,EcriAttr([§mat],[§rg_ident+1])
        run,EcriNSpace([§mat],[§rg_ident+1])
        run,ImprIdent(`>`,[§rg_ident])
      }
    }
  }

}

rout,EcriAttr(§mat,§rg_ident)
{
  runr,[§mat],T
  {
    if,"ii>0"
    {
      run,ImprIdent(`[[rr]:name]="[[rr]:value]"`,[§rg_ident])
    }
  }
}

rout,EcriNSpace(§mat,§rg_ident)
{
  runr,[§mat],Q
  {
    var,§contenu
    §contenu=xmlns
    if,"[rr]:prefix><``"
    {
      §contenu=[§contenu]:[[rr]:prefix]
    }
    §contenu=[§contenu]="[[rr]:uri]"
    run,ImprIdent(§contenu,[§rg_ident])
  }
}

rout,EnrgNSpace(§mat,§rg_ident)
{
  [RadTrad].[§rg_ident]:
  runr,[§mat],Q
  {
    [RadTrad].[§rg_ident]&Q[ii]:[[rr]:]
  }
}

rout,Qname(§mat,§rg_ident,§prc_qname)
/* Détermine le "qualified name" */
/* §mat : matricule du constructeur */
/* §rg_ident : niveau de l'élement dans l'arbre xml */
/* §prc_qname : nom da procédure qui récupère le qname */
{
  var,§qname,§uri,§prefix
  §uri=[[§mat]&T0:uri]
  run,Prefix([§uri],[§rg_ident],§prefix)
  if,"§prefix><``"
  {
    §qname=[§prefix]:[[§mat]&T0:name]
  }
  else
  {
    §qname=[[§mat]&T0:name]
  }
  [§prc_qname]=[§qname]
}

rout,Prefix(§uri,§rg_ident,§prc_prefix)
{
  var,§prefix
  §prefix=
  for,"[§rg_ident]->I","I>=0","I-1->I"
  {
    runr,comp=[RadTrad].[I],type=Q
    {
      if,"[rr]:uri==§uri"
      {
        §prefix=[[rr]:prefix]
        exit,2
      }
    }
  }
  [§prc_prefix]=[§prefix]
}
