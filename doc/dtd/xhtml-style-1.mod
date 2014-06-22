<!-- ...................................................................... -->
<!-- XHTML Document Stylesheet Module  .................................... -->
<!-- file: xhtml-style-1.mod

     This is XHTML, a reformulation of HTML as a modular XML application.
     Copyright 1998-2000 W3C (MIT, INRIA, Keio), All Rights Reserved.
     Revision: $Id: xhtml-style-1.mod,v 3.0 2000/10/22 17:13:38 altheim Exp $ SMI

     This DTD module is identified by the PUBLIC and SYSTEM identifiers:

       PUBLIC "-//W3C//DTD XHTML Stylesheets 1.0//EN"
       SYSTEM "http://www.w3.org/TR/xhtml-modularization/DTD/xhtml-style-1.mod"

     Revisions:
     (none)
     ....................................................................... -->

<!-- Stylesheets

        style

     This module declares the style element type and its attributes,
     used to embed stylesheet information in the document head element.
-->

<!-- style: Stylesheet Information ..................... -->

<!ENTITY % style.element  "INCLUDE" >
<![%style.element;[
<!ENTITY % style.content  "( #PCDATA )" >
<!ENTITY % style.qname  "style" >
<!ELEMENT %style.qname;  %style.content; >
<!-- end of style.element -->]]>

<!ENTITY % style.attlist  "INCLUDE" >
<![%style.attlist;[
<!ATTLIST %style.qname;
      %XHTML.xmlns.attrib;
      %title.attrib;
      %I18n.attrib;
      type         %ContentType.datatype;   #REQUIRED
      media        %MediaDesc.datatype;     #IMPLIED
      xml:space    ( preserve )             #FIXED 'preserve'
>
<!-- end of style.attlist -->]]>

<!-- end of xhtml-style-1.mod -->
