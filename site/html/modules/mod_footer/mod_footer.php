<?php
/**
* @version		$Id: mod_footer.php 10381 2008-06-01 03:35:53Z pasamio $
* @package		Joomla
* @copyright	Copyright (C) 2005 - 2008 Open Source Matters. All rights reserved.
* @license		GNU/GPL, see LICENSE.php
* Joomla! is free software. This version may have been modified pursuant
* to the GNU General Public License, and as distributed it includes or
* is derivative of works licensed under the GNU General Public License or
* other free or open source software licenses.
* See COPYRIGHT.php for copyright notices and details.
*/

// no direct access
defined('_JEXEC') or die('Restricted access');

global $mainframe;

$date =& JFactory::getDate();
$cur_year	= $date->toFormat('%Y');
$csite_name	= $mainframe->getCfg('sitename');

if (JString::strpos(JText :: _('FOOTER_LINE1'), '%date%')) {
	$line1 = ereg_replace('%date%', $cur_year, JText :: _('FOOTER_LINE1'));
} else {
	$line1 = JText :: _('FOOTER_LINE1');
}

if (JString::strpos($line1, '%sitename%')) {
	$lineone = ereg_replace('%sitename%', $csite_name, $line1);
} else {
	$lineone = $line1;
}

require(JModuleHelper::getLayoutPath('mod_footer'));
