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
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:html="http://www.w3.org/1999/xhtml"
    xmlns="http://www.w3.org/1999/xhtml"
    version="2.0"
>

    <xsl:output
        method="xml"
        doctype-public="-//W3C//DTD XHTML 1.1//EN"
        doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"
    />

    <!-- Insert content type into head.
      ~ @see html:title
      -->
    <xsl:template match="html:head">
        <xsl:copy>
            <xsl:apply-templates select="@*" />
            <meta http-equiv="Content-Type" content="application/xhtml+xml; charset=utf-8" />
            <xsl:apply-templates select="node()" />
        </xsl:copy>
    </xsl:template>

    <!-- Insert Stylesheet right after title, then copyright if not exists.
      ~ @see html:head
      -->
    <xsl:template match="html:title">
        <xsl:copy>
            <xsl:apply-templates select="@*|node()" />
        </xsl:copy>
        <link rel="Stylesheet" type="text/css" href="sitestyle.css" />
        <xsl:if test="not(/html:html/html:head/html:meta[name='Copyright']/@content)">
            <meta name="Copyright" content="Copyright © 2007 - 2011 The AceUnit Developers. All Rights Reserved." />
        </xsl:if>
    </xsl:template>

    <!-- Auto-generate header, heading and footer. -->
    <xsl:template match="html:body">
        <xsl:copy>
            <xsl:apply-templates select="@*" />
            <h1><img src="aceunitLogo.png" alt="AceUnit" /> <xsl:apply-templates select="/html:html/html:head/html:title/node()" /></h1>
            <xsl:apply-templates select="node()" />
            <address>
                <xsl:text>Feedback: </xsl:text><a href="mailto:cher@riedquat.de">webmaster</a>
                <br />
                <xsl:value-of select="/html:html/html:head/html:meta[@name='X-Subversion-Id']/@content" />
                <br />
                <xsl:choose>
                    <xsl:when test="/html:html/html:head/html:meta[name='Copyright']/@content">
                        <xsl:value-of select="/html:html/html:head/html:meta[name='Copyright']/@content" />
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:text>Copyright © 2007 - 2011 The AceUnit Developers. All Rights Reserved.</xsl:text>
                    </xsl:otherwise>
                </xsl:choose>
            </address>
        </xsl:copy>
    </xsl:template>

    <!-- Generate a table of contents if required. -->
    <xsl:template match="html:h2[@id='toc']">
        <h2 id="toc">Table of Contents</h2>
        <ul>
        <xsl:for-each select="/html:html/html:body/html:h2">
            <li>
                <a>
                    <xsl:attribute name="href">
                        <xsl:text>#</xsl:text>
                        <xsl:choose>
                            <xsl:when test="@id"><xsl:value-of select="@id"/></xsl:when>
                            <xsl:otherwise><xsl:value-of select="generate-id()"/></xsl:otherwise>
                        </xsl:choose>
                    </xsl:attribute>
                    <xsl:if test="@id='toc'">Table of Contents</xsl:if>
                    <xsl:apply-templates/>
                </a>
            </li>
        </xsl:for-each>
        </ul>
    </xsl:template>

    <!-- Generate ids for headings without ids so the table of contents can link to them. -->
    <xsl:template match="html:h2[not(@id)]">
        <xsl:copy>
            <xsl:attribute name="id"><xsl:value-of select="generate-id()"/></xsl:attribute>
            <xsl:apply-templates select="@*|node()" />
        </xsl:copy>
    </xsl:template>

    <!-- Everything else: Copy without change. -->
    <xsl:template match="@*|node()">
        <xsl:copy>
            <xsl:apply-templates select="@*|node()" />
        </xsl:copy>
    </xsl:template>

</xsl:transform>
