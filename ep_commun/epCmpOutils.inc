/* version 0.2 du                                                           */
/*  derni�re modification :                                                 */
/*         19 05 2015 (SD)                                                  */
/*  auteur :                                                                */
/*         SD Samuel D�om (sdeom@epadesa.fr)                                */
/*         VD Vianney Dugrain (vdugrain@epadesa.fr)                         */

/* Pour fonctionner il faut inclure pr�alablement la boite � outils         */
/*   epRalOutils                                                            */
/*   epTypeOutils (pour epRalOutils)                                        */

/* Liste des routines (en ordre alphab�tique)                               */
/*  DcompLigne(�prc_cmp,�tous_arc,�dist,�sel) d�compose une ligne en ses    */
/*           arcs �l�mentaires.                                             */
/*  MatExtL(�prc_L,�prc_matd,�prc_matf) r�cup�re le matricule du premier et */
/*           du dernier point de support d'un composant                     */
/*  MatPtN(�prc_L,�num,�prc_result) renvoi le matricule du ni�me point de   */
/*           support d'un composant                                         */
/*  NettoieSel(�prc_sel) supprime les doublons de tous les composants       */
/*           d'une s�lection                                                */
/*  NormL(�prc_cmp) normalise une ligne de mani�re � ce qu'elle commence    */
/*           par son extremit� de plus petite abscisse                      */
/*  SupprDoub(�prc_sel,�prc_cmp) supprime les doublons d'un composant       */
/*           dans une s�lection                                             */
/*  ZtoL(�cmp) Convertit des rallonges Z du composant indiqu� par �cmp en   */
/*         rallonge L                                                       */

/*--------------------------------------------------------------------------*/
/*                                ROUTINES                                  */
/*                         par ordre alphab�tique                           */
/*--------------------------------------------------------------------------*/

rout,DcompLigne(�prc_cmp,�tous_arc,�dist,�sel)
/*  Cette routine d�compose une ligne en ses arcs �l�mentaires. Chaque      */
/*      ligne cr��e conserve tous les attributs    graphiques de la ligne   */
/*      d'origine. La ligne d'origine est supprim�e. Les matricules des     */
/*      lignes cr��es gardent le radical de la ligne d'origine et           */
/*      utilisent des indices libres.                                       */
/*    La routine  traite le composant dont le matricule est contenu dans la */
/*      proc�dure donn� par la variable �prc_cmp                            */
/*    La proc�dure �sel contient le nom de la s�lection dans laquelle sont  */
/*      ajout�es les arc cr��s. Si vide les arc ne sont ajout�s � aucune.   */
/*    La proc�dure �tous_arc est un bool�en permettant d'indiquer de trai-  */
/*      ter tous les arcs �l�mentaires ou uniquement les arcs principaux.   */
/*      (aux codes * et /). Si vrai (>< 0) la ligne est aussi d�compos�e    */
/*      sur les codes #.                                                    */
/*    La proc�dure �dist permet d'indiquer, en m�tre, la longueur minimale  */
/*      en-dessous de laquelle un tron�on est �limin�. Indiquer 0 conserve  */
/*      tous les tron�ons (valeur par d�faut)                               */
/*    Cette routine est une adaptation du code de l'applicatif              */
/*       Outils Dessin -> Traiter Lignes                                    */
/*  Derni�re modification : 19 05 2015 (SD)                                 */
{
  var,�test,�cod,�long,�selOk,�bouts,�boutsup
  �bouts=0
  �boutsup=0
       
  Ligne=[[�prc_cmp]]
  
  /* On regarde s'il faut traiter tous les arcs */
  �test=0
  if,"�tous_arc><0"
  {
    �test=[valnum(�tous_arc)]
  }
  �cod=* /
  if,"�test"
  then
  {
    �cod=*#/
  }
  
  /* On regarde s'il faut supprimer les "petits" arcs */
  �test=0
  if,"�dist><0"
  {
    �test=[valnum(�dist)]
  }
  �long=0
  if,"�test"
  then
  {
    �long=[�dist]
  }
  
  /* On regarde s'il faut placer le r�sultat dans une s�lection */
  �selOk=0
  if,"�sel><``"
  then
  {
    �selOk=[defsel(�sel)]
  }
  
  runl,[Ligne],opt=0
  {
    if,typ_h /* on v�rifie qu'il ne s'agit pas d'un arc fant�me */
    {
      lin,*[deb_m]
      if,"ctr_t<>0",`lin,{ctr_c}{ctr_m}{ex}`
      if,"fin_c<<�cod"
      {
        lin,/[fin_m]
        dupl,[Ligne],[[Ligne]:R].
        if,"�selOk"
        {
          [�sel]<[mm]
        }
        lin,=[mm]
        [mm]:ph=0
        [mm]:ph=1
        gisl,[mm]
        �bouts=[�bouts+1]
        if,"�test"
        {
          if,"[mm]:L<�long"
           {
             !cmpe,[mm]
             �boutsup=[�boutsup+1]
             �bouts=[�bouts-1]
           }
        }
      }
    }
  }
  !cmpe,[Ligne]
}

rout,NettoieSel(�prc_sel)
/*  Supprime les doublons de tous les composants d'une s�lection dont le    */
/*    nom est donn� par la variable �prc_sel                                */
/*  Derni�re modification : 19 05 2015 (SD)                                 */
{
  var,�cmp,�sel
  !EpNettoieSel=
  runs,[[�prc_sel]]
  {
    �cmp=[mm]
    if,"defcmp(�cmp)"
    {
      !EpNettoieSel<[�cmp]
      if,"[�cmp]:PH=0"
      {
        �sel=([[�prc_sel]]*!test(PH=0))*~!EpNettoieSel
      }
      else
      {
        �sel=([[�prc_sel]]*!pntp([�cmp],0.1))*~!EpNettoieSel
      }
      run,SupprDoub(�sel,�cmp)
    }
  }
  !sele,!EpNettoieSel
}

rout,NormL(�prc_cmp)
/*  Normalise le composant ligne dont le matricule est contenu dans la pro- */
/*   c�dure donn� par la variable �prc_cmp                                  */
/*  La ligne est modifi�e de mani�re � ce qu'elle commence par son extremi- */
/*   t� de plus petite abscisse                                             */
/*  Derni�re modification : 19 05 2015 (SD)                                 */
{
  var,�mat
  var,�mat_deb,�mat_fin
  var,�test
  
  if,"defcmp([�prc_cmp])"
  {
    �mat=[[�prc_cmp]]
    
    run,MatExtL(�mat,�mat_deb,�mat_fin)
    
    �test=1
    if,"�mat_deb==�mat_fin"
    {
      �test=0
    }
    
    if,"�mat_deb==EpTypeVide"
    {
      �test=0
    }
    
    if,"�mat_fin==EpTypeVide"
    {
      �test=0
    }
    
    if,"�test"
    {
      if,"[�mat_deb]:X>[�mat_fin]:X"
      {
        invl,[�mat]
      }
    }
  }
}

rout,MatPtN(�prc_L,�num,�prc_result)
/*  Instancie la proc�dure contenue dans �prc_result avec le matricule du   */
/*    point de support num�ro �num du composant dont la matricule est con-  */
/*    tenu dans la proc�dure indiqu�e dans �prc_L                           */
/*  Derni�re modification : 19 05 2015 (SD)                                 */
{
  var,�mat,�resultat
  var,�i
  
  �resultat=[EpTypeVide]
  
  if,"valnum(�num)"
  {  
    if,"�num>0"
    {
      if,"defcmp([�prc_L])"
      {
        �mat=[[�prc_L]]
        runl,lign=[�mat],absc=1
        {
          if,"�num<lin_np+1"
          {
            �i=1
            runl,lign=[�mat],opt=1
            {
              if,"�i=�num"
              {
                �resultat=[deb_m]
                exit,2
              }
              else
              {
                �i=[�i+1]
              }
            }
          }
        }
      }
    }
  }
  
  [�prc_result]=[�resultat]
}

rout,MatExtL(�prc_L,�prc_matd,�prc_matf)
/*  R�cup�re le matricule du premier et du dernier point de support d'un    */
/*      composant                                                           */
/*    �prc_L contient le nom d'une proc�dure contenant le matricule du com- */
/*      posant � traiter                                                    */
/*    �prc_matd contient le nom d'une proc�dure devant r�cup�rer le matri-  */
/*      cule du premier point de support                                    */
/*    �prc_matdfcontient le nom d'une proc�dure devant r�cup�rer le matri-  */
/*      cule du dernier point de support                                    */
/*  Derni�re modification : 19 05 2015 (SD)                                 */
{
  var,�mat,�deb_m,�fin_m
  var,�i
  
  �deb_m=[EpTypeVide]
  �fin_m=[EpTypeVide]
  
  if,"defcmp([�prc_L])"
  {
    �mat=[[�prc_L]]
    �i=1
    runl,lign=[�mat],opt=1
    {
      if,"�i=1"
      {
        �deb_m=[deb_m]
      }
      
      if,"�i>=lin_np"
      {
        �fin_m=[deb_m]
      }
      else
      {
        �i=[selon(typ_h+1,�i+1,�i+1,�i+2,�i+2,�i+2,�i+2)]
      }
    }
  }
  
  [�prc_matd]=[�deb_m]
  [�prc_matf]=[�fin_m]
}

rout,SupprDoub(�prc_sel,�prc_cmp)
/*  Supprime les doublons du composant dont le nom est stock� dans la vari- */
/*    able �prc_cmp dans la s�lection de composants donn�es par la variable */
/*    proc�dure �prc_sel                                                    */
/*  Derni�re modification : 17 06 2015 (SD)                                 */
{
  var,�cmp,�ral_cmp,�ral_mm,�cpt,�mat,�jeton
  var,�fich_ref,�fich_comp
  var,�matr,�matrR,�rall,�rallR
  
  �fich_ref={base}\ref.cmp
  �fich_comp={base}\comp.cmp
  
  !SupprDoub=[[�prc_sel]]
  !SupprDoub>[[�prc_cmp]]
  
  list,file={�fich_ref},raz=1
  cmpl,[[�prc_cmp]]
  list
  
  runs,!SupprDoub
  {
    �mat=[mm]
    list,file={�fich_comp},raz=1
    cmpl,[�mat]
    list
    if,"nlfic(�fich_ref)=nlfic(�fich_comp)"
    {
      �cpt=1
      runf,file={�fich_comp},form=`�matr:�rall`
      { 
        �jeton=1
        runf,file={�fich_ref},form=`�matrR:�rallR`,ldeb=[�cpt]
        {
          if,"�rall><�rallR"
          {
            �jeton=0
            exit,2
          }
          �cpt=[�cpt+1]
        }
      }
      if,"�jeton"
      {
        rpla,[�mat],[[�prc_cmp]]
        !cmpf,[�mat]
      }
    }
  }
  !sele,!SupprDoub
}

rout,ZtoL(�cmp)
/*  Convertit des rallonges Z du composant indiqu� par �cmp en rallonge L   */
/*  Derni�re modification : 19 05 2015 (SD)                                 */
{
  var,�cmp_temp
  
  /* on cr�� une "copie" du composant en rallonge L */
  �cmp_temp=[ml(`K`)]
  dupl,[�cmp],[�cmp_temp],optn=2
  
  /* On supprime les rallonges Z du composant initial */
  runr,[�cmp],Z
  {
    [�cmp]&Z[ii]:
  }
  
  /* On recopie les rallonge L de la "copie" */
  runr,[�cmp_temp],L
  {
    [�cmp]&L[ii]:[[�cmp_temp]&L[ii]:]
  }
  
  /* On supprime la "copie" */
  !cmpe,[�cmp_temp]
}