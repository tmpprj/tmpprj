<?php
/**
 * @version		$Id: site.php 12389 2009-07-01 00:34:45Z ian $
 * @package  Joomla
 * @subpackage	Search
 * @copyright	Copyright (C) 2005 - 2008 Open Source Matters. All rights reserved.
 * @license		GNU/GPL, see LICENSE.php
 * Joomla! is free software. This version may have been modified pursuant to the
 * GNU General Public License, and as distributed it includes or is derivative
 * of works licensed under the GNU General Public License or other free or open
 * source software licenses. See COPYRIGHT.php for copyright notices and details.
 */

// Check to ensure this file is included in Joomla!
defined('_JEXEC') or die( 'Restricted access' );

/**
 * False JSite class used to fool the frontend search plugins because they route the results
 */
class JSite extends JObject
{
	/**
	 * False method to fool the frontend search plugins
	 */
	function getMenu()
	{
		$result = new JSite;
		return $result;
	}

	/**
	 * False method to fool the frontend search plugins
	 */
	function getItems()
	{
		return array();
	}
}