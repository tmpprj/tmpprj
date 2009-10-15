<?php
/**
* @version		$Id: profiler.php 10381 2008-06-01 03:35:53Z pasamio $
* @package		Joomla.Legacy
* @subpackage	1.5
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

// Register legacy classes for autoloading
JLoader::register('JProfiler', JPATH_LIBRARIES.DS.'joomla'.DS.'error'.DS.'profiler.php');


 /**
 * Legacy class, use {@link JProfiler} instead
 *
 * @deprecated	As of version 1.5
 * @package	Joomla.Legacy
 * @subpackage	1.5
 */
class mosProfiler extends JProfiler
{
	/**
	* @return object A function cache object
	*/
	function JProfiler (  $prefix=''  )
	{
		parent::__construct($prefix);
	}
}