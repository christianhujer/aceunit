<!-- ...................................................................... -->
<!-- XHTML Presentation Module ............................................ -->
<!-- file: xhtml-pres-1.mod

     This is XHTML, a reformulation of HTML as a modular XML application.
     Copyright 1998-2000 W3C (MIT, INRIA, Keio), All Rights Reserved.
     Revision: $Id: xhtml-pres-1.mod,v 3.0 2000/10/22 17:13:38 altheim Exp $ SMI

     This DTD module is identified by the PUBLIC and SYSTEM identifiers:

       PUBLIC "-//W3C//ELEMENTS XHTML Presentation 1.0//EN"
       SYSTEM "http://www.w3.org/TR/xhtml-modularization/DTD/xhtml-pres-1.mod"

     Revisions:
     (none)
     ....................................................................... -->

<!-- Presentational Elements

     This module defines elements and their attributes for
     simple presentation-related markup.
-->

<!ENTITY % xhtml-inlpres.module "INCLUDE" >
<![%xhtml-inlpres.module;[
<!ENTITY % xhtml-inlpres.mod
     PUBLIC "-//W3C//ELEMENTS XHTML Inline Presentation 1.0//EN"
            "http://www.w3.org/TR/xhtml-modularization/DTD/xhtml-inlpres-1.mod" >
%xhtml-inlpres.mod;]]>

<!ENTITY % xhtml-blkpres.module "INCLUDE" >
<![%xhtml-blkpres.module;[
<!ENTITY % xhtml-blkpres.mod
     PUBLIC "-//W3C//ELEMENTS XHTML Block Presentation 1.0//EN"
            "http://www.w3.org/TR/xhtml-modularization/DTD/xhtml-blkpres-1.mod" >
%xhtml-blkpres.mod;]]>

<!-- end of xhtml-pres-1.mod -->
