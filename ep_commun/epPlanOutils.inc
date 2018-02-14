/* version 0.1 du                                                           */
/*  dernière modification :                                                 */
/*         08 06 2015 (SD)                                                  */
/*  auteur :                                                                */
/*         SD Samuel Déom (sdeom@epadesa.fr)                                */

/* Pour fonctionner il faut inclure préalablement les boites à outils :     */
/*  epTexteOutils                                                           */
/*  epTypeOutils                                                            */

/* Procédures de l'environnement                                            */
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

proc,MdDef=EP_CAR_A2_E  /* Modèle par défaut  */
proc,EcDef=200          /* échelle par défaut */

/* Liste des routines                                                       */
/*  AutoMeP(§prc_xmil,§prc_ymil,§prc_g,§prc_ec,§prc_cx,§prc_cy,§prc_mdl,§mat_lin) */
/*  CalculeMarge Détermine les marges entre la fenêtre de vue             */
/*      effectivement tracée et les dimensions réelles du cadre du plan   */
/*        Dernière modification : 28/02/2013                              */
/*  DetFormat(§mod) Détermine le format ISO le plus proche des dimensions */
/*      données */
/*      effectivement tracée et les dimensions réelles du cadre du plan   */
/*        Dernière modification : 28/02/2013                              */
/* PubPlan(§mat_plan,§prc_dir) */
/* PresPlan(§mat_plan,§prc_nom) */
/* SuprPres(§prc_nom) */


/*--------------------------------------------------------------------------*/
/*                                ROUTINES                                  */
/*                         par ordre alphabétique                           */
/*--------------------------------------------------------------------------*/

rout,AutoMeP(§prc_xmil,§prc_ymil,§prc_g,§prc_ec,§prc_cx,§prc_cy,§prc_mdl,§mat_lin)
/* Cette routine permet une mise en page automatique d'un plan de manière à   */
/*   choisir la meilleur orientation, échelle et format pour contenir la      */
/*   dont le matricule est donné dans la procédure §mat_lin                   */
/* Le modèle appliqué au plan est celui contenu dans a procédure dont le nom  */
/*   est passé dans §prc_mdl, par défaut le modèle est celui contenu dans la  */
/*   procédure d'environnement MdDef. La procédure §mat_lin est également     */
/*   optionnelle                                                              */
/* La routine fixe une valeur aux procédures dont le nom est contenu dans les */
/*   procédures suivantes :                                                   */
/*     §prc_xmil : coordonnée x du milieu du plan                             */
/*     §prc_ymil : coordonnée y du milieu du plan                             */
/*     §prc_g    : gisement du plan                                           */
/*     §prc_ec   : échelle du plan                                            */
/*     §prc_cx   : coordonnées x du milieu du plan                            */
/*     §prc_cy   : coordonnées x du milieu du plan                            */
{
  var,§lplan,§hplan,§cx,§cy
  var,§mag,§mad,§mah,§mab
  var,§ec,§mdl
  
  §lplan={LA0}
  §hplan={HA0}
  §ec={EcDef}
  
  if,"§prc_mdl==``"
  {
    §mdl={MdDef}
  }
  else
  {
    §mdl={[§prc_mdl]}
  }
  
  run,CalculeMarge(§mdl,§mag,§mad,§mah,§mab)
  §cy=[[[§hplan-[§mah]-[§mab]]*§ec]/1000]
  §cx=[[[§lplan-[§mag]-[§mad]]*§ec]/1000]
  
  [§prc_xmil]=[[§mat_lin]:X]
  [§prc_ymil]=[[§mat_lin]:Y]
  [§prc_g]=100
  [§prc_ec]=[§ec]
  [§prc_cx]=[§cx]
  [§prc_cy]=[§cy]
}

rout,CalculeMarge(§prc_md,§prc_mag,§prc_mad,§prc_mah,§prc_mab)
/* Cette routine permet de déterminer les marges entre la fenêtre de vue  */
/*   effectivemet tracée et les dimensions réeeles du cadre du plan selon */
/*   le modèle défini dans la procédure Md, et l'échelle définie par Ec.  */
/*   Elle instancie MaG, MaD, MaH & MaB qui représente respectivement     */
/*   les marges gauche, droite, haute et basse.                           */
{
  var,§marge,§unite
  var,§mag,§mad,§mah,§mab
  
  §mag=vide
  §mad=vide
  §mah=vide
  §mab=vide
  runr,¤[[§prc_md]],K
  {
    if,"[[rr]:MG><``]"
        {
          if,"[§mag==`vide`]"
          {
            §mag=0
          }
          §marge=[xtr([rr]:MG,0,[len([rr]:MG)-2])]
          §unite=[xtr([rr]:MG,[len([rr]:MG)-2])]
          if,"§unite==`cm`"
          {
            §marge=[§marge*10]
          }
          if,"[§mag<§marge]"
          {
            §mag=[§marge]
          }
        }
        if,"[[rr]:MD><``]"
        {
          if,"[§mad==`vide`]"
          {
            §mad=0
          }
          §marge=[xtr([rr]:MD,0,[len([rr]:MD)-2])]
          §unite=[xtr([rr]:MD,[len([rr]:MD)-2])]
          if,"§unite==`cm`"
          {
            §marge=[§marge*10]
          }
          if,"[§mad<§marge]"
          {
            §mad=[§marge]
          }
        }
        if,"[[rr]:MB><``]"
        {
          if,"[§mab==`vide`]"
          {
            §mab=0
          }
          §marge=[xtr([rr]:MB,0,[len([rr]:MB)-2])]
          §unite=[xtr([rr]:MB,[len([rr]:MB)-2])]
          if,"§unite==`cm`"
          {
            §marge=[§marge*10]
          }
          if,"[§mab<§marge]"
          {
            §mab=[§marge]
          }
        }
        if,"[[rr]:MH><``]"
        {
          if,"[§mah==`vide`]"
          {
            §mah=0
          }
          §marge=[xtr([rr]:MH,0,[len([rr]:MH)-2])]
          §unite=[xtr([rr]:MH,[len([rr]:MH)-2])]
          if,"§unite==`cm`"
          {
            §marge=[§marge*10]
          }
          if,"[§mah<§marge]"
          {
            §mah=[§marge]
          }
        }
  }
  
  if,"[§mag==`vide`]"
  {
    §mag=0
  }
  if,"[§mab==`vide`]"
  {
    §mab=[§mag]
  }
  if,"[§mad==`vide`]"
  {
    §mad=[§mag]
  }
  if,"[§mah==`vide`]"
  {
    §mah=[§mag]
  }
  
  [§prc_mag]=[§mag]
  [§prc_mad]=[§mad]
  [§prc_mah]=[§mah]
  [§prc_mab]=[§mab]
}


rout,DetIso(§mat,§prc_res,§tol)
/* Cette routine permet de d'instancier la procédure contenue dans §prc_res   */
/*   avec le format ISO le plus proche des dimensions du plan                 */
/* Le format est suffixé de F (français) ou I (italien) selon que le formart  */
/*   est en portrait (F) ou paysage (I)                                       */
/* Dans le cas ou aucun format ne correspond, renvoi "vide"                   */
{
  var,§delta
  §delta=5 /* tolérance de 5mm par défaut */
  if,"valnum(§tol)"
  {
    §delta=[§tol]
  }
  
  var,§i
  var,§portrait,§format
  
  var,§mag,§mad,§mah,§mab
  var,§hplan,§lplan
  var,§mod,§cx,§cy,§ech
  

  §mod=[[§mat]:MD]
  §cx=[[§mat]:CX]
  §cy=[[§mat]:CY]
  §ech=[[§mat]&V0:Ec]
  
  run,CalculeMarge(§mod,§mag,§mad,§mah,§mab)
  
  §hplan=[[[§cy]/[§ech]]*1000+[§mah]+[§mab]]
  §lplan=[[[§cx]/[§ech]]*1000+[§mag]+[§mad]]
    

  §portrait=[§hplan>§lplan]
  
  if,"§portrait"
  {
    §lplan=[§lplan+§hplan]
    §hplan=[§lplan-§hplan]
    §lplan=[§lplan-§hplan]
  }

  §format=vide
  /* test format ISO 216 */
  for,"0->§i","§i<5","§i+1->§i"
  {
    if,"[[[§lplan]<[LA[§i]+§delta]]@[[§lplan]>[LA[§i]-§delta]]]"
    {
      if,"[[[§hplan]<[HA[§i]+§delta]]@[[§hplan]>[HA[§i]-§delta]]]"
      {
        §format=A[§i]
      }
    }
  }
  
  if,"§format==`vide`"
  {
    [§prc_res]=[§format]
  }
  else
  {
    if,"§portrait"
    {
      [§prc_res]=[§format]F
    }
    else
    {
      [§prc_res]=[§format]I
    }
  }
}

rout,DetPlan(§type,§sel,§prc_plan)
/*  Détermine le matricule correspondant au plan du même état descriptif de */
/*           division en volumes dont l'altitude est immédiatement inféri-  */
/*           eure à celle du plan actuellement tracé                        */
/*    La procédure §type doit contenir "Sup" ou "Inf" selon que l'on désire */
/*           le plan supérieur ou inférieur                                 */
/*    La procédure §sel doit contenir une procédure aboutissant à une       */
/*           sélection valide parmi laquelle le plan sera cherché           */
/*    Le matricule en renvoyé dans la procédure dont le nom est indiqué     */
/*           dans la procédure contenu dans §prc_plan                       */
/*  Dernière modification : 08 06 2015 (SD)                                 */
{
  var,§alt
  
  [§prc_plan]=[EpTypeVide]
  
  if,"[§type==`Sup`]#[§type==`Inf`]"
  {
    if,"defprc(`jtMatPlan`)"
    {
      §alt=[[jtMatPlan]:z]
      !EpTestTemp=[[§sel]]
      if,"§type==`Sup`"
      {
        runs,jtPlan*!EpTestTemp*!test(Z>[§alt]),tri={edinum(1000-{mm}:Z,3,0)})7
        {
          [§prc_plan]=[mm]
        }
      }
      else
      {
        runs,jtPlan*!EpTestTemp*!test(Z<[§alt]),tri={edinum(1000+{mm}:Z,3,0)})7
        {
          [§prc_plan]=[mm]
        }
      }
      !sele,!EpTestTemp
    }
  }
}

rout,PubPlan(§mat_plan,§prc_dir,§prc_nom)
/* Cette routine permet de publier le plan dont le matricule est passé en     */
/*   paramétre dans la procédure §mat_plan, dans le repertoire dont le nom    */
/*   est contenu dans la procédure dont le nom est donné dans §prc_dir, avec  */ 
/*   comme nom de fichier celui contenu dans la procédure dont le nom est     */
/*   donné dans §prc_nom                                                      */ 
/* Si le répertoire de publication est un sous-répertoire de la base,         */
/*   la sortie est redirigée vers [tops]\sauv                                 */
/* La routine crée une repésentation adéquate, y applique le plan, exporte au */
/*   format dxf 2004, puis supprime la présentation créée                     */
{
    var,§pres /* nom de la présentation temporaire */
    var,§nom  /* nom du fichier = indicatif court du plan si possible */
    var,§dir  /* nom du répertoire où sauvegarder le plan publié */
    var,§rep
    
    /* Repertoire par défaut */
    §dir=[tops]\sauv
    if,"len([§prc_dir])>0"
    {
      if,"1-[[§prc_dir]>>base]"
      {
        §dir={[§prc_dir]}
      }
    }
    
    /* Nom du fichier */
    §nom=[§mat_plan]
    if,"len([§prc_nom])>0"
    {
      §nom=[[§prc_nom]]
    }
    run,AtoZ(§nom,§nom)
    /* §nom=[xtr(§nom,0,)] */
    
    run,DetIso([§mat_plan],§pres,)
    if,"§pres==`vide`"
    {
      §pres=Présentation
    }
    run,SuprPres(§pres)
    run,PresPlan([§mat_plan],§pres)
    
    /* On applique le plan dans l'espace objet */
    prsa,Objet
    plna,[§mat_plan]
    
    /* On regenere */
    rgen
    
    /* On applique le plan dans la présentation */
    prsa,[§pres]
    plna,[§mat_plan]
    
    /* on exporte le dxf */
    §rep={§dir}\{§nom}
    dxf,auto=1,dir={§rep},file={§nom}.dxf,form="DXF 2004 2D",purg=15
    prsa,Objet
    run,SuprPres(§pres)
}
    
rout,PubSel(§prc_sel,§prc_dir,§form_nom)
/* Cette routine permet de publier une sélection de plan dont la formule est  */
/*   passé en paramétre dans la procédure §mat_plan, dans le repertoire dont  */
/*   le nom est contenu dans la procédure dont le nom est donné dans §prc_dir */
/*   avec comme nom de fichier le résultat de la formule contenue dans la     */
/*   procédure §form_nom                                                      */ 
{
  var,§mat,§nom
  runs,([[§prc_sel]])*jtPlan
  {
    §mat=[mm]
    §nom=[[§form_nom]]
    run,PubPlan([§mat],[§prc_dir],§nom)
  }
}

rout,SuprPres(§prc_nom)
/* Cette routine permet de supprimer une présentation adaptée au plan dont le */
/*   matricule est passé en paramétre dans la procédure §mat_plan             */
{
  var,§exist,§i,§ligne,§continu,§nl,§fic
  
  §fic=[base]\Presentations
  
  §exist=0
  §i=1
  fraj,file=[§fic]
  runf,file=[§fic],form=`b"N"r`
  {
    if,"N==[§prc_nom]"
    {
      §exist=1
      §ligne=[§i]
      §i=[§i+1]
      [fi]
    }
  }
  
  if,§exist
  {
    §continu=1
    §i=0
    §nl=[nlfic(§fic)]
    
    whil,§continu
    {
      runf,file=[§fic],form=`L(12)`,ldeb=[§ligne+§i+1]
      {
        if,"L><`Présentation`"
        {
          §i=[§i+1]
        }
        else
        {
          §continu=0
        }
      }
      if,"[§ligne+§i+1]>§nl"
      {
        §continu=0
      }
    }
    fsup,file=[§fic],lind=[§ligne],linf=[§ligne+§i]
  }
  prsf
}

rout,PresPlan(§mat_plan,§prc_nom)
/* Cette routine permet de créer une présentation adaptée au plan dont le     */
/*   matricule est passé en paramétre dans la procédure §mat_plan             */
/* le nom de la présentation est renvoyé dans la procédure dont le nom est    */
/*  donné dans §prc_nom                                                       */
{
  var,§format,§i,§portrait
  var,§cx,§cy,§ec,§md
  var,§l,§h,§larg,§haut
  var,§mah,§mab,§mag,§mad
  var,§exist
  var,§part1,§part2,§pres,§partform,§part3,§part4,§part5,§nom
  
  §cx=[[§mat_plan]:CX]
  §cy=[[§mat_plan]:CY]
  §md=[[§mat_plan]:MD]
  §ec=[[§mat_plan]&v0:ec]
  
  /* On détermine le format du plan */
  run,DetIso([§mat_plan],§format,5)
  
  if,"§format==`vide`"
  {
    §i=6
  }
  else
  {
    §i=[xtr(§format,1,1)]
  }
  
  if,"§cx>§cy"
  {
    §portrait=0
  }
  else
  {
    §portrait=1
  }

  
  if,§i<5
  {
    §format=A[§i]
    if,§portrait
    {
      §l=[H[§format]]
      §h=[L[§format]]
      §partform=[§format] (portrait)
    }
    else
    {
      §l=[L[§format]]
      §h=[H[§format]]
      §partform=[§format] (paysage)
    }
  }
  else
  {
    if,§portrait
    {
      §partform=Personnalisé (portrait)
    }
    else
    {
      §partform=Personnalisé (paysage)
    }
    run,CalculeMarge(§md,§mag,§mad,§mah,§mab)
    §h=[[§cy/§ec]*1000+[§mah]+[§mab]]
    §l=[[§cx/§ec]*1000+[§mag]+[§mad]]
  }

  §larg=[§l/10%3]
  §haut=[§h/10%3]
  
  if,"[§prc_nom]==``"
  {
    §nom=[§partform]
  }
  else
  {
    §nom=[[§prc_nom]]
  }

  §part1=Présentation"{§nom}"
  §part2=:Trac="Aucun",Form="{§partform}"
  §part3=,Opap=0,Odes=[§portrait],Fpix=397319
  §part4=,Larg={§larg},Haut={§haut}
  §part5=,Marg=0.000,Marb=0.000,Mard=0.000,Marh=0.000
  §pres={§part1}{§part2}{§part3}{§part4}{§part5}
    
  /* on verifie que la présentation n'existe pas déjà */
  §exist=0
  runf,file=[base]\Presentations,form=`b"N"r`
  {
    if,"N==§partform"
    {
      §exist=1
      [fi]
    }
  }
  /* si elle n'existe pas déjà */
  if,"§exist=0"
  {
    fraj,file=[base]\Presentations,proc=§pres
    prsf
  }
  [§prc_nom]=[§nom]
}