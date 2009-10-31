<?php
/**
* @version		$Id: head.php 11917 2009-05-29 19:37:05Z ian $
* @package		Joomla.Framework
* @subpackage	Document
* @copyright	Copyright (C) 2005 - 2008 Open Source Matters. All rights reserved.
* @license		GNU/GPL, see LICENSE.php
* Joomla! is free software. This version may have been modified pursuant
* to the GNU General Public License, and as distributed it includes or
* is derivative of works licensed under the GNU General Public License or
* other free or open source software licenses.
* See COPYRIGHT.php for copyright notices and details.
*/

// Check to ensure this file is within the rest of the framework
defined('JPATH_BASE') or die();

/**
 * JDocument head renderer
 *
 * @package		Joomla.Framework
 * @subpackage	Document
 * @since		1.5
 */
class JDocumentRendererHead extends JDocumentRenderer
{
	/**
	 * Renders the document head and returns the results as a string
	 *
	 * @access public
	 * @param string 	$name		(unused)
	 * @param array 	$params		Associative array of values
	 * @return string	The output of the script
	 */
	function render( $head = null, $params = array(), $content = null )
	{
		ob_start();

		echo $this->fetchHead($this->_doc);

		$contents = ob_get_contents();
		ob_end_clean();

		return $contents;
	}

	/**
	 * Generates the head html and return the results as a string
	 *
	 * @access public
	 * @return string
	 */
	function fetchHead(&$document)
	{
		// get line endings
		global $mainframe;
		$lnEnd = $document->_getLineEnd();
		$tab = $document->_getTab();

		$tagEnd	= ' />';

		$strHtml = '';

		// Generate base tag (need to happen first)
		$base = $document->getBase();
		if(!empty($base)) {
			$strHtml .= $tab.'<base href="'.$document->getBase().'" />'.$lnEnd;
		}

		$use_custom_default = $mainframe->getCfg('custom_default' );
		$tagEnd	= ' />';
		//
		$title = htmlspecialchars($document->getTitle());
		if ( trim($title) == trim($mainframe->getCfg('sitename' ))) {
			$title = $mainframe->getCfg('sitename' );
		} else {
			// Set the default just to the title field;
			$title = $mainframe->getCfg('html_title_config' );
			if ( empty($title)) {
				$title = "[TITLE]";
			}
			$title = str_replace( "[TITLE]",htmlspecialchars($document->getTitle()), $title );
			$title = str_replace( "[SITENAME]",$mainframe->getCfg('sitename' ) , $title );
		}

		$strHtml = '';
		$strHtml	= $tab . '<title>' . htmlspecialchars($title) . '</title>' . $lnEnd;
		// Set some metatag information if needed
		if ($mainframe->getCfg('MetaTitle') == '1') {
			$document->setMetaData('title', $title );
		}

		// Generate base tag (need to happen first)
		$base = $document->getBase();
		if(!empty($base)) {
			$strHtml .= $tab.'<base href="'.$document->getBase().'" />'.$lnEnd;
		}
		/*
		 * Read the default XML file (if defaults are used) todoo
		 */
		if ($use_custom_default) {
			$xml = & JFactory::getXMLParser('Simple');
			$xml->loadFile( JPATH_ROOT . DS . 'metaconfig.xml');

			$obj = & $xml->document->params['0'];
			$custom_meta_array = array();
			$exclude_list = array("html_title","meta_description", "meta_keywords", "robots" );
			foreach ( $obj->_children as $child) {
				if ( $child->_attributes['default'] != "" & !in_array($child->_attributes['name'], $exclude_list)) {
					$custom_meta_array[$child->_attributes['name']]['value']=$child->_attributes['default'];
					$custom_meta_array[$child->_attributes['name']]['is_set']=FALSE;
				}
			}
		}

		// Generate META tags
		// check if keywords or description tag is set, if not the global value can be set.
		$metaDescription_used 	= false;
		$metaKeywords_used 		= false;
		$metaRobots_used 		= false;
		$strHtml_meta 			= "";
		$strHtml_equiv 			= "";
		$arr = $document->_metaTags;

		foreach ($document->_metaTags as $type => $tag)	{

			foreach ($tag as $name => $content)	{
				$name = str_replace('meta_','',$name );
				if ( $name == "robots") {
					$metaRobots_used = true;									}
				if ( $content != '') {
					if ($type == 'http-equiv') {
						$strHtml_equiv .= $tab . "<meta http-equiv=\"$name\" content=\"$content\"" . $tagEnd . $lnEnd;
					} elseif ($type == 'standard') {
						$strHtml_meta .= $tab . "<meta name=\"$name\" content=\"$content\"" . $tagEnd . $lnEnd;
						if ( $name == "keywords") {
							$metaKeywords_used = true;
						}
						if ( $name == "description") {
							$metaDescription_used = true;
						}
					}
					if ( $use_custom_default) {
						if ( array_key_exists( $name, $custom_meta_array)) {
							$custom_meta_array[$name]['is_set'] = TRUE;

						}
					}
				}
			}
		}
		if ( !$metaDescription_used) {
			// Fetch the document description tag;
			if ( isset($document->description) ) {
				if (!empty($document->description)) {
					$strHtml .= $tab . "<meta name=\"description\" content=\"" . $document->description . "\"/>" . $lnEnd;
					$metaDescription_used = true;
				}
			}
		}
		if ( !$metaDescription_used) {
			$metaDescription = $mainframe->getCfg('MetaDesc' );
			if ( ($mainframe->getCfg('use_global_metadesc') == 1) & ($metaDescription != "" ) ) {
				$strHtml .= $tab . "<meta name=\"description\" content=\"" . $metaDescription . "\"/>" . $lnEnd;
			}
		}

		if ( !$metaKeywords_used) {
			$metaKeywords = $mainframe->getCfg('MetaKeys' );
			if ( ($mainframe->getCfg('use_global_keywords') == 1) & ($metaKeywords != "" ) ) {
				$strHtml .= $tab . "<meta name=\"keywords\" content=\"" . $metaKeywords . "\"/>" . $lnEnd;
			}
		}
		if ( !$metaRobots_used ) {
			$metaRobots = $mainframe->getCfg('metarobots' );
			if ( $metaRobots != "0" & $metaRobots != "") {
				$strHtml .= $tab . "<meta name=\"robots\" content=\"" . $metaRobots . "\"/>" . $lnEnd;
			}
		}

		# make sure that the description META tag and keywords are displayed first, then the custom tags and then the http-equiv
		$strHtml .=$strHtml_meta;
		if ( $use_custom_default) {
			foreach ( $custom_meta_array as $name => $value ) {
				if ($value['is_set'] == FALSE ) {
					$strHtml .= $tab . '<meta name="'. $name . '" content="' . $value['value'] . '" />' . $lnEnd;
				}
			}
		}
		# JAW: check if empty, don't display if empty
		if ( $mainframe->getCfg('metagenerator' ) == "1" & ($mainframe->getCfg('generator_tag' ) != '' )) {
			$strHtml .= $tab . '<meta name="generator" content="' . $mainframe->getCfg('generator_tag' ) . '" />' . $lnEnd;
		}
		// Generate link declarations
		foreach ($document->_links as $link) {
			$strHtml .= $tab.$link.$tagEnd.$lnEnd;
		}

		// Generate stylesheet links
		foreach ($document->_styleSheets as $strSrc => $strAttr )
		{
			$strHtml .= $tab . '<link rel="stylesheet" href="'.$strSrc.'" type="'.$strAttr['mime'].'"';
			if (!is_null($strAttr['media'])){
				$strHtml .= ' media="'.$strAttr['media'].'" ';
			}
			if ($temp = JArrayHelper::toString($strAttr['attribs'])) {
				$strHtml .= ' '.$temp;;
			}
			$strHtml .= $tagEnd.$lnEnd;
		}

		// Generate stylesheet declarations
		foreach ($document->_style as $type => $content)
		{
			$strHtml .= $tab.'<style type="'.$type.'">'.$lnEnd;

			// This is for full XHTML support.
			if ($document->_mime == 'text/html' ) {
				$strHtml .= $tab.$tab.'<!--'.$lnEnd;
			} else {
				$strHtml .= $tab.$tab.'<![CDATA['.$lnEnd;
			}

			$strHtml .= $content . $lnEnd;

			// See above note
			if ($document->_mime == 'text/html' ) {
				$strHtml .= $tab.$tab.'-->'.$lnEnd;
			} else {
				$strHtml .= $tab.$tab.']]>'.$lnEnd;
			}
			$strHtml .= $tab.'</style>'.$lnEnd;
		}

		// Generate script file links
		foreach ($document->_scripts as $strSrc => $strType) {
			$strHtml .= $tab.'<script type="'.$strType.'" src="'.$strSrc.'"></script>'.$lnEnd;
		}

		// Generate script declarations
		foreach ($document->_script as $type => $content)
		{
			$strHtml .= $tab.'<script type="'.$type.'">'.$lnEnd;

			// This is for full XHTML support.
			if ($document->_mime != 'text/html' ) {
				$strHtml .= $tab.$tab.'<![CDATA['.$lnEnd;
			}

			$strHtml .= $content.$lnEnd;

			// See above note
			if ($document->_mime != 'text/html' ) {
				$strHtml .= $tab.$tab.'// ]]>'.$lnEnd;
			}
			$strHtml .= $tab.'</script>'.$lnEnd;
		}

		foreach($document->_custom as $custom) {
			$strHtml .= $tab.$custom.$lnEnd;
		}

		return $strHtml;
	}
}