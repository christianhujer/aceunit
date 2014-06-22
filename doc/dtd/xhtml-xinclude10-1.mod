<?xml version="1.0" encoding="utf-8"?>
<!-- vim:set filetype=dtd: -->
<!--
  - $Id: xhtml-xinclude-1.mod,v 1.1 2004/06/02 18:10:56 chris Exp $
  -
  - XHTML DTD Module for XInclude
  -->

<!ENTITY % XInclude.prefixed "INCLUDE">

<!ENTITY % XInclude.prefix
    "xi"
>
<!ENTITY % XInclude.xmlns
    "http://www.w3.org/2001/XInclude"
>
<![%XInclude.prefixed;[
    <!ENTITY % XInclude.pfx  "%XInclude.prefix;:">
    <!ENTITY % XInclude.pfxd ":%XInclude.prefix;">
]]>
<!ENTITY % XInclude.pfx "">
<!ENTITY % XInclude.xmlns.attrib "xmlns%XInclude.pfxd; CDATA #FIXED '%XInclude.xmlns;'">

<!ENTITY % XHTML.xmlns.extra.xi.attrib
    " %XInclude.xmlns.attrib; "
>

<!ENTITY % xinclude.qname "%XInclude.pfx;include">
<!ENTITY % fallback.qname "%XInclude.pfx;fallback">
<!ENTITY % xinclude.content "%fallback.qname;?">

<!ELEMENT %xinclude.qname; (%xinclude.content;)>
<!ATTLIST %xinclude.qname;
    %XInclude.xmlns.attrib;
    href            CDATA       #IMPLIED
    parse           (xml|text)  "xml"
    xpointer        CDATA       #IMPLIED
    encoding        CDATA       #IMPLIED
    accept          CDATA       #IMPLIED
    accept-language CDATA       #IMPLIED
>
<!ELEMENT %fallback.qname; ANY>
<!ATTLIST %fallback.qname;
    %XInclude.xmlns.attrib;
>

<!ENTITY % XInclude.base.attrib "
    xml:base        CDATA       #IMPLIED
">

<!ENTITY % Common.extra.xinclude.attrib "
    %XInclude.base.attrib;
">
