<?php
/**
* @version		$Id: admin.cpanel.html.php 10559 2008-07-16 20:57:43Z instance $
* @package		Joomla
* @subpackage	Admin
* @copyright	Copyright (C) 2005 - 2008 Open Source Matters. All rights reserved.
* @license		GNU/GPL, see LICENSE.php
* Joomla! is free software. This version may have been modified pursuant
* to the GNU General Public License, and as distributed it includes or
* is derivative of works licensed under the GNU General Public License or
* other free or open source software licenses.
* See COPYRIGHT.php for copyright notices and details.
*/

// no direct access
defined( '_JEXEC' ) or die( 'Restricted access' );

jimport('joomla.html.pane');
jimport('joomla.application.module.helper');

/**
* @package		Joomla
* @subpackage	Admin
*/
class HTML_cpanel
{
	/**
	* Control panel
	*/
	function display()
	{
		global $mainframe;

		$modules = &JModuleHelper::getModules('cpanel');
        // TODO: allowAllClose should default true in J!1.6, so remove the array when it does.
		$pane = &JPane::getInstance('sliders', array('allowAllClose' => true));
		echo $pane->startPane("content-pane");

		foreach ($modules as $module) {
			$title = $module->title ;
			echo $pane->startPanel( $title, 'cpanel-panel-'.$module->name );
			echo JModuleHelper::renderModule($module);
			echo $pane->endPanel();
		}

		echo $pane->endPane();
	}
}