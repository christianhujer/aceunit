<?xml version="1.0" encoding="utf-8"?>
<!--
  ~ Copyright (c) 2007 - 2011, Christian Hujer
  ~ All rights reserved.
  ~ 
  ~ Redistribution and use in source and binary forms, with or without
  ~ modification, are permitted provided that the following conditions are met:
  ~     * Redistributions of source code must retain the above copyright
  ~       notice, this list of conditions and the following disclaimer.
  ~     * Redistributions in binary form must reproduce the above copyright
  ~       notice, this list of conditions and the following disclaimer in the
  ~       documentation and/or other materials provided with the distribution.
  ~     * Neither the name of the AceUnit developers nor the
  ~       names of its contributors may be used to endorse or promote products
  ~       derived from this software without specific prior written permission.
  ~ 
  ~ THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  ~ "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  ~ LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  ~ A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
  ~ OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
  ~ EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
  ~ PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
  ~ PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  ~ LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  ~ NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  ~ SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  -->
<xsl:transform
    version="2.0"
    xmlns:html="http://www.w3.org/1999/xhtml"
    xmlns:xml="http://www.w3.org/XML/1998/namespace"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    exclude-result-prefixes="html"
    xmlns:saxon="http://saxon.sf.net/"
>

    <!-- Ausgabe: HTML 4.01 / UTF-8 -->
    <xsl:output
        method="html"
        doctype-public="-//W3C//DTD HTML 4.01//EN"
        doctype-system="http://www.w3.org/TR/html4/strict.dtd"
        indent="no"
        encoding="utf-8"
        media-type="text/html"
        omit-xml-declaration="yes"
    />
    <!---
        saxon:character-representation="native;hex"
    -->

    <!-- XHTML-Processing-Instructions löschen. -->
    <xsl:template match="processing-instruction('doc')"/>
    <xsl:template match="processing-instruction('xml-stylesheet')"/>

    <!-- PHP Processing Instructions als Processing Instruction ausgeben.
      - Sonst wird aus ?> nur >
      -->
    <xsl:template match="processing-instruction('php')">
        <xsl:processing-instruction name="php"><xsl:value-of select="."/>?</xsl:processing-instruction>
    </xsl:template>
    <xsl:template match="processing-instruction('cgi')">
        <xsl:processing-instruction name="cgi"><xsl:value-of select="."/>?</xsl:processing-instruction>
    </xsl:template>

    <!-- Ursprüngliches Content-Type-Meta löschen -->
    <xsl:template match="html:meta[@http-equiv='Content-Type']"/>

    <!-- Überflüssige Default-Attribute löschen. -->
    <xsl:template match="html:head/@profile"/>
    <xsl:template match="html:html/@version"/>
    <xsl:template match="html:td/@rowspan[.='1']|html:td/@colspan[.='1']|html:th/@rowspan[.='1']|html:th/@colspan[.='1']"/>
    <xsl:template match="html:a/@shape[.='rect']"/>

    <!-- Inhalt und CData-Sektionen bei style und script in Kommentare verwandeln. -->
    <xsl:template match="html:style">
        <xsl:element
            name="{local-name()}"
        >
            <xsl:apply-templates select="@*"/>
            <xsl:comment>
                <xsl:apply-templates/>
            </xsl:comment>
        </xsl:element>
    </xsl:template>
    <xsl:template match="html:script">
        <xsl:element
            name="{local-name()}"
        >
            <xsl:apply-templates select="@*"/>
            <xsl:comment>
                <xsl:text>//&#xA;
</xsl:text>
                <xsl:apply-templates/>
                <xsl:text>&#xA;//</xsl:text>
            </xsl:comment>
        </xsl:element>
    </xsl:template>

    <!-- xml:lang-Attribut als lang-Attribut ausgeben -->
    <xsl:template match="@xml:lang">
        <xsl:attribute name="lang">
            <xsl:value-of select="." />
        </xsl:attribute>
    </xsl:template>

    <!-- xml:space-Attribut löschen -->
    <xsl:template match="@xml:space"/>

    <!-- id-Attribut als name-Attribut kopieren -->
    <xsl:template match="html:a/@id">
        <xsl:copy/>
        <xsl:attribute name="name">
            <xsl:value-of select="."/>
        </xsl:attribute>
    </xsl:template>

    <!-- type="application/xhtml+xml" durch type="text/html" ersetzen -->
    <xsl:template match="@type[.='application/xhtml+xml']">
        <xsl:attribute name="type">text/html</xsl:attribute>
    </xsl:template>

    <!-- Replace XHTML validity by HTML validity -->
    <xsl:template match="html:img[@src='http://www.w3.org/Icons/valid-xhtml11' and @alt='Valid XHTML 1.1']/@alt"/>
    <xsl:template match="html:img[@src='http://www.w3.org/Icons/valid-xhtml11' and @alt='Valid XHTML 1.1']/@href"/>
    <xsl:template match="html:img[@src='http://www.w3.org/Icons/valid-xhtml11' and @alt='Valid XHTML 1.1']">
        <xsl:element
            name="{local-name()}"
        >
            <xsl:apply-templates select="@*"/>
            <xsl:attribute name="src">http://www.w3.org/Icons/valid-html401</xsl:attribute>
            <xsl:attribute name="alt">Valid HTML 4.01!</xsl:attribute>
            <xsl:apply-templates select="node()"/>
        </xsl:element>
    </xsl:template>

    <!-- Fix table border to be of value 1 -->
    <xsl:template match="html:table/@border[.='border']">
        <xsl:attribute name="border">1</xsl:attribute>
    </xsl:template>

    <!-- Ausgabe ohne XML-Namespaces -->
    <xsl:template match="html:*">
        <xsl:element
            name="{local-name()}"
        >
            <xsl:apply-templates select="@*"/>
            <xsl:apply-templates select="node()"/>
        </xsl:element>
    </xsl:template>

    <!--
      - Den Rest des Baumes 1:1 kopieren.
      -->
    <xsl:template match="@*|node()">
        <xsl:copy>
            <xsl:apply-templates select="@*|node()"/>
        </xsl:copy>
    </xsl:template>
</xsl:transform>
