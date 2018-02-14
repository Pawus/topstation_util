/*                              ROUTINES                                                                                                                                                */
/*                                                                                                                                                                                              */
/* BarProgInit(§mes)                    Initialise une barre de progression avec le message §mes                */
/* BarProgMaj(§i,§ntot)                 Met à jour la barre de progression si §i/§ntot varie de 1%              */
/* BriChain(§sell)                                              Brise les chaines d'une sélection de lignes et les met                  */
/*                                                                              dans la sélection !HbSell                                                               */
/* CherPntProPnt(§selp,§pnt,§dis)               Cherche le point dans §selp le plus proche d'un                                 */
/*                                                                              point §pnt dans un rayon §dis et le met dans                                    */
/*                                                                              hbTemp.[hbbIndMin+100]&q0:pnt                                                                           */
/* CherLgnProPnt(§sell,§pnt,§dis)               Cherche la ligne dans §sell la plus proche d'un                                 */
/*                                      point §pnt dans un rayon §dis et la met dans            */
/*                                      hbTemp.[hbbIndMin+100]&q0:lgn; si pas de ligne =0       */
/* ChProActi(§fep)                                              retourne l'état du projet actif de l'EDDV concerné par le projet §fep                           */
/*                                                                              ETPR = matricule EDDV ou vide;matricule projet actif ou vide;Nb indices ou 0;indice actif ou 0  */
/* Confirm(§mes)                        Confirmation (OUI: hbOui=1   /   NON: hbOui=0)                                                  */
/* Conv_m2_ha(§aire)                    Convertit les m2 en hectares ares centiares - résultat dans hbTems              */
/* CreJ1pLO(§lib,§rad,§md)              Crée un composant §rad avec modèle ponctuel orientable justifié sur un  */
/*                                      point existant ou de radical [%cmp.p:rad]; s'il est à proximité d'une   */
/*                                      ligne comprise dans !HbSell, il sera projeté dessus; la ligne est       */
/*                                      enregistrée dans hbTemp.[hbbIndMin+100]&q0:lgn                          */
/* DebFonc                              Début d'une fonction ordinaire environnement TOPSTATION                                 */
/* DomAjout                             Ajoute un ou plusieurs composants dans le domaine du plan */
/* DomDispo(§debnomdom)                 Recherche du premier domaine disponible entre 1 et 100 000              */
/*                                                              commençant par §debnomdom                                                                               */
/*                                      Définit la procédure temporaire hbTemp=[§debnomdom][Numéro]                         */
/* DomainesPlan(§jtPlan)                                Retourne le contenu de %dom:dom de la ligne k d'indice le plus élevé dans hbTemd        */
/* Erreur(§mes)                         Affiche dans un menu popup le message d'erreur contenu dans §mes */
/* FicEcr(§lib,§chem,§nomfic,§routform) Ecriture d'un fichier §nomfic dans §chem par la                 */
/*                                      procédure §routform; l'aide de la fonction aura                                                         */
/*                                      pour nom §routform.txt                                                                                                          */
/* MajImgDxfCad                         Mise à jour de !JtImgCad et !JtDxfCad                                                   */
/*                                      Mise à jour (temporaire si pas de marque) des composants représentatifs des planches DXF-PCI */
/*                                      c'est-à-dire ajout des rallonges &V40: et &V41: sur les composants ayant &V0/1:ly==1SUBDSECT */
/* MajInd                               Met à jour les index dans une base      */
/* Message(§mes)                Affiche un message revient sur la fenêtre précédente en cliquant sur OK */
/* MessageFdia(§mes)    Affiche un message et ferme toutes les fenêtres en cliquant sur OK              */
/* Pcal                                 Calcul d'un point provisoire */
/* Presenta(§nom,§fo,§jtPlan,§xmil,§ymil)       Crée ou met à jour la présentation de nom §nom et de format §fo et applique le plan §jtPlan selon §xmil et §ymil */
/* StatutEddv(§fed)             Retourne dans hbTemp le statut de l'EDDV   ACTUEL  ou PROJET NOUVEL EDDV  ou PROJET EDDV MODIFICATIF    */
/*                                          ETEV=[ACTUEL[PROJET]];[indice];[matricule du projet]                                                                                */
/* TitDos(§dos)         met dans [mm] le matricule du titre des plans du dossier §dos                           */
/* VerifFonc            Vérifie et fait la mise à jour des composants et index nécessaires à des requêtes sur des composants du foncier   */
/* VerifOncles(§nom,§mat)       Vérifie si un composant [§mat] de nom [§nom] a des oncles et affiche la liste. Procédure hbOui=1 s'il en a et hbOui=0 s'il n'en a pas */



rout,BarProgInit(§mes)
{
  hbTemb=0
  dial,HB_BARPROG,l=530,h=20,tx={§mes}
  qc,pg,ID=HB_PG,X=10,Y=7,L=510,H=10,ET=0,INFO=`Barre de progression du programme en cours`
}


rout,BarProgMaj(§i,§ntot)
{
  var,§j

  §j=[§i*100/§ntot%0]
  if,"§j><hbTemb"
  {
    qmod,id=HB_PG,et=[§j=>hbTemb]
  }
}

                                                                /* Brise les chaines d'une sélection de lignes          */
rout,BriChain(§sell)            /* les met dans la sélection !HbSell                            */
{
  var,§l

  runs,[§sell]
  {
    runl,[mm=>§l],opt=0
    {
      if,"deb_m><`0`"
      {
        lin,cma=[deb_c][deb_m]
      }
      if,"ctr_t>0"
      {
        lin,cma=[ctr_c][ctr_m]
      }
      if,"deb_t=3"
      {
        dupl,[§l],[ml(`[§l]`)],optn=0
        lin,cma="=[mm]"
        !HbSell<[mm]
      }
      if,"deb_t=4"
      {
        lin,cma="=[§l]"
        !HbSell<[mm]
      }
    }
  }
}

                                /* Cherche la ligne dans §sell la plus proche d'un      */
                                /* point §pnt dans un rayon §dis et la met dans         */
                                /* hbTemp.[hbbIndMin+100]&q0:lgn                        */

rout,CherLgnProPnt(§sell,§pnt,§dis)
{
  var,§t

  ral,hbTemp.[hbbIndMin+100]&q0:lgn=0
  runs,[§sell]*!linp([§pnt],[§dis])
  {
    dipl,pnt=[§pnt],lign=[mm],prct=§t
    if,"abs([§t])<abs([§dis])"
    {
      hbTemp.[hbbIndMin+100]&q0:lgn=[mm]
      §dis=[§t]
    }
  } 
}

rout,CherPntProPnt(§selp,§pnt,§dis)
{
  var,§t

  ral,hbTemp.[hbbIndMin+100]&q0:pnt=0
  runs,[§selp]*!pntp([§pnt],[§dis])
  {
    dipp,pnt1=[§pnt],pnt2=[mm],prcd=§t
    if,"abs([§t])<abs([§dis])"
    {
      hbTemp.[hbbIndMin+100]&q0:pnt=[mm]
      §dis=[§t]
    }
  }
}

rout,ChProActi(§fep)            /* retourne l'état du projet actif de l'EDDV concerné par le projet §fep                                */
{                                                       /* ETPR = matricule EDDV ou vide;matricule projet actif ou vide;Nb indices ou 0;indice actif ou 0       */
        var,§a,§fed,§fep1,§i,§indacti,§j,§nbind
        
        §nbind=0
        §indacti=0
        ETPR=;;[§nbind];[§indacti]
        if,"[§fep]&q1:type==`Nouvel EDDV`"
        {
                §fed={}
                §fep1=[§fep]
                §a=abcd
                for,1->§j,§j<5,§j+1->§j
                {
                        dcod,text=§a,form=`§i(1)§a`
                        if,"[§fep]&r0:[§i]><``"
                        {
                                §nbind=[§nbind+1]
                                if,"[[§fep]&r0:[§i]]:r==hbcFED"
                                {
                                        §indacti=[§i]
                                }
                        }
                }
        }
        else
        {
                §fed=[[§fep]&r0:E]      
                if,"[§fep]&q1:type==`Suppression d’EDDV`"
                {
                        §fep1=[§fep]
                        if,"[§fep]&r0:O><``"
                        {
                                §nbind=1
                                if,"[§fed]:r==hbcFEd"
                                {
                                        §indacti=a                      /*      Suppression d'EDDV actif        */
                                }
                        }
                }
                else
                {
                    if,"[§fed]:r==hbcFED"
                        {
                                §fep1=[§fep]                            /* Tous les projets modif & suppr sont désactivés. On garde §fep */                                             
                        }
                        else
                        {
                            runs,[hbcFep]*!onc([§fed])*!onc([hbcFED])   /* !onc([hbcFED]) donne le seul projet actif    */
                                {
                                        §fep1=[mm]
                                }
                        }
                        §a=abcd
                        for,1->§j,§j<5,§j+1->§j
                        {
                                dcod,text=§a,form=`§i(1)§a`
                                if,"[§fep]&r0:[§i]><``"
                                {
                                        §nbind=[§nbind+1]
                                        if,"[[§fep]&r0:[§i]]:r==hbcFED"
                                        {
                                                §indacti=[§i]   
                                        }
                                }
                        }
                }
        }
        ETPR=[§fed];[§fep1];[§nbind];[§indacti]
}

rout,Confirm(§mes)
{
  qpop,"[§mes] ?",j=5
  {
    qap,tx="Oui",proc=HbOui
    qap,tx="Non",proc=HbNon
  }

  rout,HbOui
  {
    hbOui=1
  }

  rout,HbNon
  {
    hbOui=0
  }
}

rout,Conv_m2_ha(§aire)
{
  var,§a,§aca,§ca,§ha

  §aire=[§aire%0]
  §aca=[mod(§aire,10000)]
  §ha=[[§aire-§aca]/10000]
  §ca=[mod(§aca,100)]
  §a=[[§aca-§ca]/100]
  hbTems={}
  if,"§a<>0"    
  {
    if,"§ha<>0"  /* §a<>0 et §ha<>0 */
    {
      hbTems=[§ha] ha [§a)02] a [§ca)02] ca
    }
    else         /* §a<>0 et §ha=0 */
    {
      hbTems=[§a] a [§ca)02] ca
    }
  }
  else          /* §a=0 et §ha<>0 */
  {  
    if,"§ha<>0"
    {
      hbTems=[§ha] ha 00 a [§ca)02] ca
    }
    else        /* §a=0 et §ha=0  */
    {
      hbTems=[§ca] ca
    }
  }
}

rout,CreJ1pLO(§lib,§rad,§md)
{
  var,§i,§pj,§t

  hbTempX=
  hbTempY=
  hbTempIv=1
  §i=0
  §pj=
  §t=Symbole [§lib]
  Xc=[60+4]
  Yc=[12+4]
  dial,id=HB,l=[4+3*Xc],h=[2*4+2*Yc],tx={§t}
  qc,tx,HB_TX,[4],[§i*Yc+4],[2*60],[12],j=2,tx="Point de justification :"
  qc,tx,HB_TXXMM,[2*Xc-60+4],[§i*Yc+4],[60/4],[12],j=8,tx="X:"
  qc,ed,HB_XMM,[6*4+2*Xc-60],[§i*Yc+4],[60-60/3],[12],tdig=XDIG,rout=CreJ1pLOXY,tx=[hbTempX]
  qc,tx,HB_TXYMM,[3*Xc-60],[§i*Yc+4],[60/4],[12],j=8,tx="Y:"
  qc,ed,HB_YMM,[6*4+3*Xc-60-4],[§i*Yc+4],[60-60/3],[12],tdig=YDIG,rout=CreJ1pLOXY,tx=[hbTempY]
  §i=[§i+1]
  qc,bf,HB_OK,[4],[§i*Yc+2*4],[60],[12],j=5,tx="OK",rout=CreJ1pLO1
  qc,bf,HB_AIDE,[4+2*Xc],[§i*Yc+2*4],[60],[12],j=5,tx="Aide",rout=CreJ1pLOAide
  qset,foc=HB_XMM,mod=0


  rout,CreJ1pLOXY
  {
    if,"[tx(HB_XMM)><``]@[tx(HB_YMM)><``]"
    {
      if,"`[hbTempIv]`==`1`"
      {
        hbTempIv=0
        hbOui=1
      }
      hbTempIv=0
      hbTemp.[hbbIndMin]:x=[tx(HB_XMM)],y=[tx(HB_YMM)],ph=2
      hbTempX=[tx(HB_XMM)]
      hbTempY=[tx(HB_YMM)]
      [§rad]:x=[hbTempX],y=[hbTempY],ph=2
      §pj=[mm]
    }
  }

  rout,CreJ1pLOAide
  {
    aide,[hbLum]\Aide\CreJ1pLO.txt
  }

  rout,CreJ1pLO1
  {
    if,"§pj><``"
    {
      if,"§pj==`hbTemp.[hbbIndMin]`"
      {
        rmat,[mm],[%cmp.p:rad]
        §pj=[mm]
      }
      run,CreJ1pLO2([§rad],[§md],[§pj])
    }
    else
    {
      qpop,tx=Cliquer dans le plan ou remplir les coordonnées
    }
  }
}

rout,CreJ1pLO2(§rad,§md,§pj)
{
  hbTemp.[hbbIndMin+100]&q0:lgn=""
  if,"hbdCre=1" /* projection sur une ligne uniquement pour un point nouveau */
  {
    run,CherLgnProPnt(!HbSell,[§pj],5)
    if,"hbTemp.[hbbIndMin+100]&q0:lgn><`0`"
    {
      prjl,[§pj],[hbTemp.[hbbIndMin+100]&q0:lgn],proc=Pcal
      rmat,[mm],[cmp.p:rad]
      §pj=[mm]
    }
  }
  [§pj]:md=[%cmp.p:md]
  [§rad]&j0:a=[§pj]
  §rad=[mm]
  [§rad]:md=[§md],cx=3
  run,DomAjout([§rad]+[§pj])
}




/* D */

                                                        /* Début d'une fonction ordinaire environnement TOPSTATION      */
rout,DebFonc
{
  hbTeme=0
  hbTemp=0
  hbTemq=0
  hbTems=0
                                        /* Composants */
  !cmpe,hbTem.[hbbIndMin]/hbTemz.[hbbIndMax]
}


rout,DomAjout(§cmp)
{
  domi,dom=[[jtMatPlan]&d0:],sel=[§cmp]
}

rout,DomDispo(§debnomdom)
{
  var,§num

  for,"1->§num","§num<=100000","§num+1->§num"
  {
    if,"defdom(`[§debnomdom][§num]`)=0"
    {
      hbTemp=[§debnomdom][§num]         /* 1er domaine disponible */
      if,"len(hbTemp)>31"
      {
        qpop,Nom de domaine [hbTemp] trop long (31 caractères maximum)
        [ha]
      }
      [fi]
    }
  }
}  

rout,DomainesPlan(§jtPlan)
{
  var,§l
  hbTemd={}
  runr,[§jtPlan],type=k
  {
    if,"[[rr]:>>`%dom:dom`]#[[rr]:>>`%DOM:DOM`]"
    {
      §l=[len([rr]:)]
      hbTemd=[xtr([rr]:,10,[§l-11])]
    }
  }
}


/* F */
                                        /* Ecriture d'un fichier */

rout,FicEcr(§lib,§chem,§nomfic,§routform)
{
  var,§nomfich

  !JtPnts=0
  Xc=[60+4]
  Yc=[12+4]

  run,FicNomMaj([§chem][§nomfic])
  §nomfich=[hbTemp]

  dial,FIC_ECR,l=[4+3*Xc],h=[4+2*Yc],tx={§lib}
  qc,bf,BF_F,[4],[4],[60],[12],j=5,tx="Fichier",rout=FicEcrFile([§chem],[§nomfich])
  qc,ed,ED_FICECRFILE,[Xc+4],[4],[60+Xc],[12],tx="{§nomfich}"
  qc,bf,BF_FICECROK,[4],[Yc+4],[60],[12],j=5,tx="OK",rout=FicEcrExec([§nomfich],[§routform])
  qc,bf,BF_FICECRAIDE,[2*Xc+4],[Yc+4],[60],[12],j=5,tx="Aide",rout=FicEcrAide([§routform])
  
  evnt,entr=FicEcrExec([§nomfich],[§routform])
  qset,foc=ED_FICECRFILE,mod=0
}

rout,FicEcrFile(§chem,§nomfich)
{
  chfi,prop=[§chem],exis=0,ok=BfFichOK

  rout,BfFichOK(§nomfic)
  {

    if,"§nomfic><``"
    {
      §nomfich=[§nomfic]
      qmod,ED_FICECRFILE,tx="[§nomfich]"
    }
  }
}

rout,FicEcrExec(§nomfich,§routform)
{
  hbReponse=0
  if,"§nomfich><``"
  {
    §nomfich=[tx(ED_FICECRFILE)]
    run,FicExist([§nomfich])
    if,"hbReponse"
    {
      run,FicEcrExecu([§nomfich],[§routform])
    }
  }
}

rout,FicEcrAide(§routform)
{
  Aide,file=[hbDir]\Exports\Aide\[§routform].txt
}
  
rout,FicEcrExecu(§nomfich,§routform)
{
  list,[§nomfich]
  run,[§routform]([§nomfich])
}

rout,FicNomMaj(§fic)
{
  if,"syst_u"
  {
    prct,§fic,ancn=\,nouv=/
  }
  else
  {
    prct,§fic,ancn=/,nouv=\
  }
  hbTemp=[§fic]
} 

rout,FicExist(§nom)                             /* test de l'existence d'un fichier en vue d'opérations d'écriture */
{
  hbReponse=0
  if,"nlfic(`[§nom]`)=-2"
  {
    run,Message(Veuillez introduire un nom de fichier correct)
  }
  if,"nlfic(`[§nom]`)=-1"
  {
    hbReponse=1
  }
  if,"nlfic(`[§nom]`)>=0"
  {
    run,Confirm(Le fichier existe déjà : voulez-vous le supprimer)
    if,"hbOui"
    {
      list,file=[§nom],raz=1
      list
      hbReponse=1
    }
  }
}

/* Affiche dans un menu popup le message d'erreur contenu dans §mes */
rout,Erreur(§mes)
{
  note
  qpop,{§mes},j=5
}


/* Mise à jour de !JtImgCad et !JtDxfCad */
/* Mise à jour (temporaire si pas de marque) des composants représentatifs des planches DXF-PCI */
/* c'est-à-dire ajout des rallonges &V40: et &V41: sur les composants ayant &V0/1:ly==1SUBDSECT */
/* la remarque 'temporaire' n'est valable que pour les fichiers DXF repris avec gcDxfIn */
/* (sinon !test(&V40:Commune><``) devrait trouver ces composants caractéristiques des planches cadastre) */
rout,MajImgDxfCad
{
  var,§commune,§section,§feuille,§ech,§qual
  !JtImgCad=0
  !JtDxfCad=0
  runs,!test(&V2:Im><``)*!test(&V40:Commune><``)*!test(&V40:Echelle><``)
  { /* Composants caractéristiques des planches cadastre Image TIFF de la base en cours */
    !JtImgCad<[mm]
  }
  runs,!test(&V0:ly==1SUBDSECT)+!test(&V1:ly==1SUBDSECT)
  { /* Composants caractéristiques des planches cadastre DXF-PCI de la base en cours reprises avec gcDxfIn ou D.A.> Importer fichier DXF-PCI */
    §commune=¹inconnue¹
    §section=¹inconnue¹
    §feuille=¹inconnue¹
    §ech=¹inconnue¹
    §qual=¹inconnue¹
    runr,comp=[mm],type=V
    {
      if,"[rr]:QUPL><``"
      {
        §qual=[xtr([rr]:QUPL,0,2)]
        if,"xtr([§qual],0,1)==`0`","xtr([§qual],1,1)->§qual"
      }
      if,"[rr]:EOR><``"
      {
        §ech=[xtr([rr]:EOR,0)]
        whil,"{xtr(§ech,0,1)==`0`}@{len(§ech)>1}","{xtr(§ech,1)}->§ech" /* (enlever les 0 à gauche) */
      }
      if,"[rr]:IDU><``"
      {
        §commune=[xtr([rr]:IDU,0,3)]
        §section=[xtr([rr]:IDU,6,2)]
        if,"xtr(§section,0,1)==`0`","xtr(§section,1,1)->§section"
        §feuille=[xtr([rr]:IDU,8,2)] /* A vérifier: est-ce bien la feuille ? */
        if,"xtr(§feuille,0,1)==`0`","xtr(§feuille,1,1)->§feuille"
      }
    }
    /* &V40 pour aller au-delà des rallonges V existantes sur ce composant */
    [mm]&V40:Commune=[§commune],Section=[§section],Feuille=[§feuille],Echelle=[§ech],Qual=[§qual]
    [mm]&V41:Type=DXF
    !JtDxfCad<[mm]
  }
}

rout,MajInd
{
        /* Index des parcelles: HBCPAR */
        if,"defind(`HBCPAR`)=0"
        {
                >HBCPAR:RAD=[hbcPar],CLE1=&V1:DEP(3),CLE2=&V1:COM(3),CLE3=&V1:PRE(3),CLE4=&V1:SEC(2),CLE5=&V1:NUM(4.0)
                                                                                                                /* 4.0 pour un entier positif jusqu'à 4 chiffres */
        }
        /* Index des parcelles: HBCPAF */
        if,"defind(`HBCPAF`)=0"
        {
                >HBCPAF:RAD=[hbcPaf],CLE1=&V1:DEP(3),CLE2=&V1:COM(3),CLE3=&V1:PRE(3),CLE4=&V1:SEC(2),CLE5=&V1:NUM(4.0)
                                                                                                                /* 4.0 pour un entier positif jusqu'à 4 chiffres */
        }
}

rout,Message(§mes)              /* Affiche un message et revient sur la fenêtre précédente en cliquant sur OK */
{
  Xc=[60+4]
  Yc=[12+4]
  if,"len(§mes)<15"
  {
    dial,HB_MESSAGE,l=[4+Xc],h=[4+2*Yc],tx=Information
    qc,tx,TXMESSAGE,[4],[4],[4+Xc],[12],ft=2,j=5,tx=[§mes]
    qc,bf,BFMESSAGE,[4],[4+Yc],[60],[12],j=5,tx="OK",rout=BfMessage
  }
  else
  {
    dial,HB_MESSAGE,l=[2*4+[len(§mes)]*5],h=[4+2*Yc],tx=Information
    qc,tx,TXMESSAGE,[4],[4],[2*4+[len(§mes)]*5],[12],ft=2,j=5,tx=[§mes]
    qc,bf,BFMESSAGE,[arn(4+[[len(§mes)]*5-60]/2,2)],[4+Yc],[60],[12],j=5,tx="OK",rout=BfMessage
  }

  evnt,entr=,bdro=BfMessage

  rout,BfMessage
  {
    rdia
  }
}

rout,MessageFdia(§mes)          /* Affiche un message et ferme toutes les fenêtres en cliquant sur OK */
{
  Xc=[60+4]
  Yc=[12+4]
  if,"len(§mes)<15"
  {
    dial,HB_MESSAGE,l=[4+Xc],h=[4+2*Yc],tx=Information
    qc,tx,TXMESSAGE,[4],[4],[4+Xc],[12],ft=2,j=5,tx=[§mes]
    qc,bf,BFMESSAGE,[4],[4+Yc],[60],[12],j=5,tx="OK",rout=BfMessageF
  }
  else
  {
    dial,HB_MESSAGE,l=[2*4+[len(§mes)]*4],h=[4+2*Yc],tx=Information
    qc,tx,TXMESSAGE,[4],[4],[2*4+[len(§mes)]*4],[12],ft=2,j=5,tx=[§mes]
    qc,bf,BFMESSAGE,[4+[[len(§mes)]*4-60]/2],[4+Yc],[60],[12],j=5,tx="OK",rout=BfMessageF
  }

  evnt,entr=,bdro=BfMessageF

  rout,BfMessageF
  {
    Fdia
  }
}


/* ------------------- Calcul d'un point provisoire ------------------------ */
rout,Pcal
{
  [ml(`hbTemp.[hbbIndMin]`)]:[xc],[yc],ph=1
}


rout,Presenta(§nom,§fo,§jtPlan,§xmil,§ymil,§co)
{
  prsf
  var,§fic,§fpix,§posfic,§t1a,§t1b,§t2
  
  lanc,NomBurInit,{hbDir}/Param/NomBur          /* Initialisation des paramètres bureau */

  §fic=[nombase]\Presentations
  §nom=Présentation"[§nom] [§fo]"
  §posfic=[posfic(`[§fic]`,`[§nom]`)]
  §t2=[§jtPlan]"[[§jtPlan]&v0:nom]":Xmil=[§xmil],Ymil=[§ymil]

  if,"[§co]=1"  /* Noir et blanc */
  {
    §fpix=196865
  }
  if,"[§co]=2"  /* Nuances de gris */
  {
    §fpix=67584
  }
  if,"[§co]=3"  /* 256 couleurs */
  {
    §fpix=198659
  }
  if,"[§co]=4"  /* 16 bits */
  {
    §fpix=397319
  }
  if,"[§co]=5"  /* 24 bits */
  {
    §fpix=137224
  }
  if,"[§co]=6"  /* 32 bits */
  {
    §fpix=2498570
  }

  if,"§posfic<=0"
  {
    if,"§fo==`A4`"
    {
      §t1a=[§nom]:Trac="[TracA4]",Form="A4 (portrait)",Opap=1,Odes=1,Fpix=[§fpix],Larg=21.000,Haut=29.700
    }
    else
    {
      §t1a=[§nom]:Trac="[TracA3]",Form="A3 (paysage)",Opap=0,Odes=0,Fpix=[§fpix],Larg=42.000,Haut=29.700
    }
    §t1b=Marg=[Marg[§fo]],Marb=[Marb[§fo]],Mard=[Mard[§fo]],Marh=[Marh[§fo]]
    fraj,file=[§fic],proc=`{§t1a},{§t1b}`
    fraj,file=[§fic],proc=§t2
  }
  else
  {
    fmod,file=[§fic],line=[§posfic+1],proc=§t2
  }
  prsf
}


Rout,StatutEddv(§fed)
{
        hbTemp=ACTUEL
        ETEV=ACTUEL;;
        if,"nmbr(`[hbcFep]*!onc([§fed])`)"
        {
                runs,[hbcFep]*!onc([§fed])
                {
                        if,"[mm]&r0:E==§fed"
                        {
                                hbTemp=ACTUEL
                                ETEV=ACTUEL;;
                        }
                        else
                        {
                                if,"[mm]&r0:A==§fed"
                                {
                                        hbTemp=PROJET indice a
                                        ETEV=PROJET;a;[mm]
                                }
                                if,"[mm]&r0:B==§fed"
                                {
                                        hbTemp=PROJET indice b
                                        ETEV=PROJET;b;[mm]
                                }
                                if,"[mm]&r0:C==§fed"
                                {
                                        hbTemp=PROJET indice c
                                        ETEV=PROJET;c;[mm]                                      
                                }
                                if,"[mm]&r0:D==§fed"
                                {
                                        hbTemp=PROJET indice d
                                        ETEV=PROJET;d;[mm]
                                }
                        }
                        [fi]    /* traite une anomalie éventuelle */
                }
        }
}


rout,TitDos(§dos)
{
  if,"nmbr(`HTI*!test(&q0:ir==[[§dos]&q0:ir])`)"
  {
    runs,HTI*!test(&q0:ir==[[§dos]&q0:ir])
    {
      [mm]:ph=0
    }
  }
  else
  {
    qpop,tx="Préparer d'abord les titres de plans du dossier choisi"
    [ha]
  }
}

rout,VerifFonc
{
        /* Table des usages     */
        if,"defcmp(`hbbFld.1`)=0"
        {
                hbbFld.1&V0:nat="Local Technique",nab=LT,mdl=hbf_coupeloted_lt
                hbbFld.1&V1:nat="Galerie Technique",nab=GT,mdl=hbf_coupeloted_gt
                hbbFld.1&V2:nat="Dalle",nab=DA,mdl=hbf_coupeloted_da
                hbbFld.1&V3:nat="Circulation Piétonnière",nab=CP,mdl=hbf_coupeloted_cp
                hbbFld.1&V4:nat="Voie de Desserte",nab=VD,mdl=hbf_coupeloted_vd
                hbbFld.1&V5:nat="Voie Routière",nab=VR,mdl=hbf_coupeloted_vr
                hbbFld.1&V6:nat="Parc de Stationnement",nab=PS,mdl=hbf_coupeloted_ps
                hbbFld.1&V7:nat="Pilier Mur",nab=PM,mdl=hbf_coupeloted_pm
                hbbFld.1&V8:nat="Local Commercial",nab=LC,mdl=hbf_coupeloted_lc
                hbbFld.1&V9:nat="Activité Bureau",nab=AB,mdl=hbf_coupeloted_ab
                hbbFld.1&V10:nat="Activité service Publique",nab=AP,mdl=hbf_coupeloted_ap
                hbbFld.1&V11:nat="Local d'Habitation",nab=LH,mdl=hbf_coupeloted_lh
                hbbFld.1&V12:nat="Terrain Lot",nab=TL,mdl=hbf_coupeloted_tl
                hbbFld.1&V13:nat="Lot Résiduel",nab=LR,mdl=hbf_coupeloted_lr
                hbbFld.1&V14:nat="Autre",nab=AU,mdl=hbf_coupeloted_au
                !cmpe,hbbFld.1,ral=d
        }   
    run,MajInd
}

rout,VerifOncles(§nom,§mat)
{
  var,§titr

  §titr=Vérification de [§nom] [§mat]
  !HbOncles=!onc([§mat])

  if,"[nmbr(`!HbOncles`)]>0"
  {
    hbOui=1
    list,file=[base]\LISTING,raz=1
    impq,`Le composant [§nom] [§mat] est lié aux composants suivants:`
    impq,` `
    rdcl,!onc([§mat])
    impq,` `
    impq,` `
    impq,`Cette sélection a été sauvegardée dans !HbOncles`
    list
    afli,file=[base]\LISTING,titr={§titr}
  }
  else
  {
    hbOui=0
  }
}
