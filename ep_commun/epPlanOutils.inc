/* version 0.1 du                                                           */
/*  derni�re modification :                                                 */
/*         08 06 2015 (SD)                                                  */
/*  auteur :                                                                */
/*         SD Samuel D�om (sdeom@epadesa.fr)                                */

/* Pour fonctionner il faut inclure pr�alablement les boites � outils :     */
/*  epTexteOutils                                                           */
/*  epTypeOutils                                                            */

/* Proc�dures de l'environnement                                            */
proc,LA0=1189
proc,HA0=841
proc,LA1=841
proc,HA1=594
proc,LA2=594
proc,HA2=420
proc,LA3=420
proc,HA3=297
proc,LA4=297
proc,HA4=210

proc,MdDef=EP_CAR_A2_E  /* Mod�le par d�faut  */
proc,EcDef=200          /* �chelle par d�faut */

/* Liste des routines                                                       */
/*  AutoMeP(�prc_xmil,�prc_ymil,�prc_g,�prc_ec,�prc_cx,�prc_cy,�prc_mdl,�mat_lin) */
/*  CalculeMarge D�termine les marges entre la fen�tre de vue             */
/*      effectivement trac�e et les dimensions r�elles du cadre du plan   */
/*        Derni�re modification : 28/02/2013                              */
/*  DetFormat(�mod) D�termine le format ISO le plus proche des dimensions */
/*      donn�es */
/*      effectivement trac�e et les dimensions r�elles du cadre du plan   */
/*        Derni�re modification : 28/02/2013                              */
/* PubPlan(�mat_plan,�prc_dir) */
/* PresPlan(�mat_plan,�prc_nom) */
/* SuprPres(�prc_nom) */


/*--------------------------------------------------------------------------*/
/*                                ROUTINES                                  */
/*                         par ordre alphab�tique                           */
/*--------------------------------------------------------------------------*/

rout,AutoMeP(�prc_xmil,�prc_ymil,�prc_g,�prc_ec,�prc_cx,�prc_cy,�prc_mdl,�mat_lin)
/* Cette routine permet une mise en page automatique d'un plan de mani�re �   */
/*   choisir la meilleur orientation, �chelle et format pour contenir la      */
/*   dont le matricule est donn� dans la proc�dure �mat_lin                   */
/* Le mod�le appliqu� au plan est celui contenu dans a proc�dure dont le nom  */
/*   est pass� dans �prc_mdl, par d�faut le mod�le est celui contenu dans la  */
/*   proc�dure d'environnement MdDef. La proc�dure �mat_lin est �galement     */
/*   optionnelle                                                              */
/* La routine fixe une valeur aux proc�dures dont le nom est contenu dans les */
/*   proc�dures suivantes :                                                   */
/*     �prc_xmil : coordonn�e x du milieu du plan                             */
/*     �prc_ymil : coordonn�e y du milieu du plan                             */
/*     �prc_g    : gisement du plan                                           */
/*     �prc_ec   : �chelle du plan                                            */
/*     �prc_cx   : coordonn�es x du milieu du plan                            */
/*     �prc_cy   : coordonn�es x du milieu du plan                            */
{
  var,�lplan,�hplan,�cx,�cy
  var,�mag,�mad,�mah,�mab
  var,�ec,�mdl
  
  �lplan={LA0}
  �hplan={HA0}
  �ec={EcDef}
  
  if,"�prc_mdl==``"
  {
    �mdl={MdDef}
  }
  else
  {
    �mdl={[�prc_mdl]}
  }
  
  run,CalculeMarge(�mdl,�mag,�mad,�mah,�mab)
  �cy=[[[�hplan-[�mah]-[�mab]]*�ec]/1000]
  �cx=[[[�lplan-[�mag]-[�mad]]*�ec]/1000]
  
  [�prc_xmil]=[[�mat_lin]:X]
  [�prc_ymil]=[[�mat_lin]:Y]
  [�prc_g]=100
  [�prc_ec]=[�ec]
  [�prc_cx]=[�cx]
  [�prc_cy]=[�cy]
}

rout,CalculeMarge(�prc_md,�prc_mag,�prc_mad,�prc_mah,�prc_mab)
/* Cette routine permet de d�terminer les marges entre la fen�tre de vue  */
/*   effectivemet trac�e et les dimensions r�eeles du cadre du plan selon */
/*   le mod�le d�fini dans la proc�dure Md, et l'�chelle d�finie par Ec.  */
/*   Elle instancie MaG, MaD, MaH & MaB qui repr�sente respectivement     */
/*   les marges gauche, droite, haute et basse.                           */
{
  var,�marge,�unite
  var,�mag,�mad,�mah,�mab
  
  �mag=vide
  �mad=vide
  �mah=vide
  �mab=vide
  runr,�[[�prc_md]],K
  {
    if,"[[rr]:MG><``]"
        {
          if,"[�mag==`vide`]"
          {
            �mag=0
          }
          �marge=[xtr([rr]:MG,0,[len([rr]:MG)-2])]
          �unite=[xtr([rr]:MG,[len([rr]:MG)-2])]
          if,"�unite==`cm`"
          {
            �marge=[�marge*10]
          }
          if,"[�mag<�marge]"
          {
            �mag=[�marge]
          }
        }
        if,"[[rr]:MD><``]"
        {
          if,"[�mad==`vide`]"
          {
            �mad=0
          }
          �marge=[xtr([rr]:MD,0,[len([rr]:MD)-2])]
          �unite=[xtr([rr]:MD,[len([rr]:MD)-2])]
          if,"�unite==`cm`"
          {
            �marge=[�marge*10]
          }
          if,"[�mad<�marge]"
          {
            �mad=[�marge]
          }
        }
        if,"[[rr]:MB><``]"
        {
          if,"[�mab==`vide`]"
          {
            �mab=0
          }
          �marge=[xtr([rr]:MB,0,[len([rr]:MB)-2])]
          �unite=[xtr([rr]:MB,[len([rr]:MB)-2])]
          if,"�unite==`cm`"
          {
            �marge=[�marge*10]
          }
          if,"[�mab<�marge]"
          {
            �mab=[�marge]
          }
        }
        if,"[[rr]:MH><``]"
        {
          if,"[�mah==`vide`]"
          {
            �mah=0
          }
          �marge=[xtr([rr]:MH,0,[len([rr]:MH)-2])]
          �unite=[xtr([rr]:MH,[len([rr]:MH)-2])]
          if,"�unite==`cm`"
          {
            �marge=[�marge*10]
          }
          if,"[�mah<�marge]"
          {
            �mah=[�marge]
          }
        }
  }
  
  if,"[�mag==`vide`]"
  {
    �mag=0
  }
  if,"[�mab==`vide`]"
  {
    �mab=[�mag]
  }
  if,"[�mad==`vide`]"
  {
    �mad=[�mag]
  }
  if,"[�mah==`vide`]"
  {
    �mah=[�mag]
  }
  
  [�prc_mag]=[�mag]
  [�prc_mad]=[�mad]
  [�prc_mah]=[�mah]
  [�prc_mab]=[�mab]
}


rout,DetIso(�mat,�prc_res,�tol)
/* Cette routine permet de d'instancier la proc�dure contenue dans �prc_res   */
/*   avec le format ISO le plus proche des dimensions du plan                 */
/* Le format est suffix� de F (fran�ais) ou I (italien) selon que le formart  */
/*   est en portrait (F) ou paysage (I)                                       */
/* Dans le cas ou aucun format ne correspond, renvoi "vide"                   */
{
  var,�delta
  �delta=5 /* tol�rance de 5mm par d�faut */
  if,"valnum(�tol)"
  {
    �delta=[�tol]
  }
  
  var,�i
  var,�portrait,�format
  
  var,�mag,�mad,�mah,�mab
  var,�hplan,�lplan
  var,�mod,�cx,�cy,�ech
  

  �mod=[[�mat]:MD]
  �cx=[[�mat]:CX]
  �cy=[[�mat]:CY]
  �ech=[[�mat]&V0:Ec]
  
  run,CalculeMarge(�mod,�mag,�mad,�mah,�mab)
  
  �hplan=[[[�cy]/[�ech]]*1000+[�mah]+[�mab]]
  �lplan=[[[�cx]/[�ech]]*1000+[�mag]+[�mad]]
    

  �portrait=[�hplan>�lplan]
  
  if,"�portrait"
  {
    �lplan=[�lplan+�hplan]
    �hplan=[�lplan-�hplan]
    �lplan=[�lplan-�hplan]
  }

  �format=vide
  /* test format ISO 216 */
  for,"0->�i","�i<5","�i+1->�i"
  {
    if,"[[[�lplan]<[LA[�i]+�delta]]@[[�lplan]>[LA[�i]-�delta]]]"
    {
      if,"[[[�hplan]<[HA[�i]+�delta]]@[[�hplan]>[HA[�i]-�delta]]]"
      {
        �format=A[�i]
      }
    }
  }
  
  if,"�format==`vide`"
  {
    [�prc_res]=[�format]
  }
  else
  {
    if,"�portrait"
    {
      [�prc_res]=[�format]F
    }
    else
    {
      [�prc_res]=[�format]I
    }
  }
}

rout,DetPlan(�type,�sel,�prc_plan)
/*  D�termine le matricule correspondant au plan du m�me �tat descriptif de */
/*           division en volumes dont l'altitude est imm�diatement inf�ri-  */
/*           eure � celle du plan actuellement trac�                        */
/*    La proc�dure �type doit contenir "Sup" ou "Inf" selon que l'on d�sire */
/*           le plan sup�rieur ou inf�rieur                                 */
/*    La proc�dure �sel doit contenir une proc�dure aboutissant � une       */
/*           s�lection valide parmi laquelle le plan sera cherch�           */
/*    Le matricule en renvoy� dans la proc�dure dont le nom est indiqu�     */
/*           dans la proc�dure contenu dans �prc_plan                       */
/*  Derni�re modification : 08 06 2015 (SD)                                 */
{
  var,�alt
  
  [�prc_plan]=[EpTypeVide]
  
  if,"[�type==`Sup`]#[�type==`Inf`]"
  {
    if,"defprc(`jtMatPlan`)"
    {
      �alt=[[jtMatPlan]:z]
      !EpTestTemp=[[�sel]]
      if,"�type==`Sup`"
      {
        runs,jtPlan*!EpTestTemp*!test(Z>[�alt]),tri={edinum(1000-{mm}:Z,3,0)})7
        {
          [�prc_plan]=[mm]
        }
      }
      else
      {
        runs,jtPlan*!EpTestTemp*!test(Z<[�alt]),tri={edinum(1000+{mm}:Z,3,0)})7
        {
          [�prc_plan]=[mm]
        }
      }
      !sele,!EpTestTemp
    }
  }
}

rout,PubPlan(�mat_plan,�prc_dir,�prc_nom)
/* Cette routine permet de publier le plan dont le matricule est pass� en     */
/*   param�tre dans la proc�dure �mat_plan, dans le repertoire dont le nom    */
/*   est contenu dans la proc�dure dont le nom est donn� dans �prc_dir, avec  */ 
/*   comme nom de fichier celui contenu dans la proc�dure dont le nom est     */
/*   donn� dans �prc_nom                                                      */ 
/* Si le r�pertoire de publication est un sous-r�pertoire de la base,         */
/*   la sortie est redirig�e vers [tops]\sauv                                 */
/* La routine cr�e une rep�sentation ad�quate, y applique le plan, exporte au */
/*   format dxf 2004, puis supprime la pr�sentation cr��e                     */
{
    var,�pres /* nom de la pr�sentation temporaire */
    var,�nom  /* nom du fichier = indicatif court du plan si possible */
    var,�dir  /* nom du r�pertoire o� sauvegarder le plan publi� */
    var,�rep
    
    /* Repertoire par d�faut */
    �dir=[tops]\sauv
    if,"len([�prc_dir])>0"
    {
      if,"1-[[�prc_dir]>>base]"
      {
        �dir={[�prc_dir]}
      }
    }
    
    /* Nom du fichier */
    �nom=[�mat_plan]
    if,"len([�prc_nom])>0"
    {
      �nom=[[�prc_nom]]
    }
    run,AtoZ(�nom,�nom)
    /* �nom=[xtr(�nom,0,)] */
    
    run,DetIso([�mat_plan],�pres,)
    if,"�pres==`vide`"
    {
      �pres=Pr�sentation
    }
    run,SuprPres(�pres)
    run,PresPlan([�mat_plan],�pres)
    
    /* On applique le plan dans l'espace objet */
    prsa,Objet
    plna,[�mat_plan]
    
    /* On regenere */
    rgen
    
    /* On applique le plan dans la pr�sentation */
    prsa,[�pres]
    plna,[�mat_plan]
    
    /* on exporte le dxf */
    �rep={�dir}\{�nom}
    dxf,auto=1,dir={�rep},file={�nom}.dxf,form="DXF 2004 2D",purg=15
    prsa,Objet
    run,SuprPres(�pres)
}
    
rout,PubSel(�prc_sel,�prc_dir,�form_nom)
/* Cette routine permet de publier une s�lection de plan dont la formule est  */
/*   pass� en param�tre dans la proc�dure �mat_plan, dans le repertoire dont  */
/*   le nom est contenu dans la proc�dure dont le nom est donn� dans �prc_dir */
/*   avec comme nom de fichier le r�sultat de la formule contenue dans la     */
/*   proc�dure �form_nom                                                      */ 
{
  var,�mat,�nom
  runs,([[�prc_sel]])*jtPlan
  {
    �mat=[mm]
    �nom=[[�form_nom]]
    run,PubPlan([�mat],[�prc_dir],�nom)
  }
}

rout,SuprPres(�prc_nom)
/* Cette routine permet de supprimer une pr�sentation adapt�e au plan dont le */
/*   matricule est pass� en param�tre dans la proc�dure �mat_plan             */
{
  var,�exist,�i,�ligne,�continu,�nl,�fic
  
  �fic=[base]\Presentations
  
  �exist=0
  �i=1
  fraj,file=[�fic]
  runf,file=[�fic],form=`b"N"r`
  {
    if,"N==[�prc_nom]"
    {
      �exist=1
      �ligne=[�i]
      �i=[�i+1]
      [fi]
    }
  }
  
  if,�exist
  {
    �continu=1
    �i=0
    �nl=[nlfic(�fic)]
    
    whil,�continu
    {
      runf,file=[�fic],form=`L(12)`,ldeb=[�ligne+�i+1]
      {
        if,"L><`Pr�sentation`"
        {
          �i=[�i+1]
        }
        else
        {
          �continu=0
        }
      }
      if,"[�ligne+�i+1]>�nl"
      {
        �continu=0
      }
    }
    fsup,file=[�fic],lind=[�ligne],linf=[�ligne+�i]
  }
  prsf
}

rout,PresPlan(�mat_plan,�prc_nom)
/* Cette routine permet de cr�er une pr�sentation adapt�e au plan dont le     */
/*   matricule est pass� en param�tre dans la proc�dure �mat_plan             */
/* le nom de la pr�sentation est renvoy� dans la proc�dure dont le nom est    */
/*  donn� dans �prc_nom                                                       */
{
  var,�format,�i,�portrait
  var,�cx,�cy,�ec,�md
  var,�l,�h,�larg,�haut
  var,�mah,�mab,�mag,�mad
  var,�exist
  var,�part1,�part2,�pres,�partform,�part3,�part4,�part5,�nom
  
  �cx=[[�mat_plan]:CX]
  �cy=[[�mat_plan]:CY]
  �md=[[�mat_plan]:MD]
  �ec=[[�mat_plan]&v0:ec]
  
  /* On d�termine le format du plan */
  run,DetIso([�mat_plan],�format,5)
  
  if,"�format==`vide`"
  {
    �i=6
  }
  else
  {
    �i=[xtr(�format,1,1)]
  }
  
  if,"�cx>�cy"
  {
    �portrait=0
  }
  else
  {
    �portrait=1
  }

  
  if,�i<5
  {
    �format=A[�i]
    if,�portrait
    {
      �l=[H[�format]]
      �h=[L[�format]]
      �partform=[�format] (portrait)
    }
    else
    {
      �l=[L[�format]]
      �h=[H[�format]]
      �partform=[�format] (paysage)
    }
  }
  else
  {
    if,�portrait
    {
      �partform=Personnalis� (portrait)
    }
    else
    {
      �partform=Personnalis� (paysage)
    }
    run,CalculeMarge(�md,�mag,�mad,�mah,�mab)
    �h=[[�cy/�ec]*1000+[�mah]+[�mab]]
    �l=[[�cx/�ec]*1000+[�mag]+[�mad]]
  }

  �larg=[�l/10%3]
  �haut=[�h/10%3]
  
  if,"[�prc_nom]==``"
  {
    �nom=[�partform]
  }
  else
  {
    �nom=[[�prc_nom]]
  }

  �part1=Pr�sentation"{�nom}"
  �part2=:Trac="Aucun",Form="{�partform}"
  �part3=,Opap=0,Odes=[�portrait],Fpix=397319
  �part4=,Larg={�larg},Haut={�haut}
  �part5=,Marg=0.000,Marb=0.000,Mard=0.000,Marh=0.000
  �pres={�part1}{�part2}{�part3}{�part4}{�part5}
    
  /* on verifie que la pr�sentation n'existe pas d�j� */
  �exist=0
  runf,file=[base]\Presentations,form=`b"N"r`
  {
    if,"N==�partform"
    {
      �exist=1
      [fi]
    }
  }
  /* si elle n'existe pas d�j� */
  if,"�exist=0"
  {
    fraj,file=[base]\Presentations,proc=�pres
    prsf
  }
  [�prc_nom]=[�nom]
}