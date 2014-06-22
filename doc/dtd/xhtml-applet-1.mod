<!-- ...................................................................... -->
<!-- XHTML Java Applet Module  ............................................ -->
<!-- file: xhtml-applet-1.mod

     This is XHTML, a reformulation of HTML as a modular XML application.
     Copyright 1998-2000 W3C (MIT, INRIA, Keio), All Rights Reserved.
     Revision: $Id: xhtml-applet-1.mod,v 3.1 2000/11/15 22:02:08 altheim Exp $ SMI

     This DTD module is identified by the PUBLIC and SYSTEM identifiers:

       PUBLIC "-//W3C//ELEMENTS XHTML Java Applets 1.0//EN"
       SYSTEM "http://www.w3.org/TR/xhtml-modularization/DTD/xhtml-applet-1.mod"

     Revisions:
     (none)
     ....................................................................... -->

<!-- Java Applets

        applet

     This module declares the applet element type and its attributes, 
     used to provide support for Java applets. The 'alt' attribute 
     is now required (as it is on images). One of either code or 
     object attributes must be present. In the document, place param 
     elements before other content within the <applet> element.

     Note that use of this module requires instantiation of the 
     Param Element Module.
-->

<!-- applet: Java Applet ............................... -->

<!ENTITY % applet.element  "INCLUDE" >
<![%applet.element;[
<!ENTITY % applet.content
     "( %param.qname; | %Flow.mix; | #PCDATA )*"
>
<!ENTITY % applet.qname  "applet" >
<!ELEMENT %applet.qname;  %applet.content; >
<!-- end of applet.element -->]]>

<!ENTITY % applet.attlist  "INCLUDE" >
<![%applet.attlist;[
<!ATTLIST %applet.qname;
      %Core.attrib;
      alt          %Text.datatype;          #REQUIRED
      archive      CDATA                    #IMPLIED
      code         CDATA                    #IMPLIED
      codebase     %URI.datatype;           #IMPLIED
      object       CDATA                    #IMPLIED
      width        %Length.datatype;        #REQUIRED
      height       %Length.datatype;        #REQUIRED
>
<!-- end of applet.attlist -->]]>

<!-- end of xhtml-applet-1.mod -->
