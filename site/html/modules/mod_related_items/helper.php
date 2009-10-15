<?php
/**
* @version		$Id: helper.php 11137 2008-10-15 19:47:01Z kdevine $
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

require_once (JPATH_SITE.DS.'components'.DS.'com_content'.DS.'helpers'.DS.'route.php');

class modRelatedItemsHelper
{
	function getList($params)
	{
		global $mainframe;

		$db					=& JFactory::getDBO();
		$user				=& JFactory::getUser();

		$option				= JRequest::getCmd('option');
		$view				= JRequest::getCmd('view');

		$temp				= JRequest::getString('id');
		$temp				= explode(':', $temp);
		$id					= $temp[0];

		$showDate			= $params->get('showDate', 0);

		$nullDate			= $db->getNullDate();


		$date =& JFactory::getDate();
		$now  = $date->toMySQL();

		$related			= array();

		if ($option == 'com_content' && $view == 'article' && $id)
		{

			// select the meta keywords from the item
			$query = 'SELECT metakey' .
					' FROM #__content' .
					' WHERE id = '.(int) $id;
			$db->setQuery($query);

			if ($metakey = trim($db->loadResult()))
			{
				// explode the meta keys on a comma
				$keys = explode(',', $metakey);
				$likes = array ();

				// assemble any non-blank word(s)
				foreach ($keys as $key)
				{
					$key = trim($key);
					if ($key) {
						$likes[] = ',' . $db->getEscaped($key) . ','; // surround with commas so first and last items have surrounding commas
					}
				}

				if (count($likes))
				{
					// select other items based on the metakey field 'like' the keys found
					$query = 'SELECT a.id, a.title, DATE_FORMAT(a.created, "%Y-%m-%d") AS created, a.sectionid, a.catid, cc.access AS cat_access, s.access AS sec_access, cc.published AS cat_state, s.published AS sec_state,' .
							' CASE WHEN CHAR_LENGTH(a.alias) THEN CONCAT_WS(":", a.id, a.alias) ELSE a.id END as slug,'.
							' CASE WHEN CHAR_LENGTH(cc.alias) THEN CONCAT_WS(":", cc.id, cc.alias) ELSE cc.id END as catslug'.
							' FROM #__content AS a' .
							' LEFT JOIN #__content_frontpage AS f ON f.content_id = a.id' .
							' LEFT JOIN #__categories AS cc ON cc.id = a.catid' .
							' LEFT JOIN #__sections AS s ON s.id = a.sectionid' .
							' WHERE a.id != '.(int) $id .
							' AND a.state = 1' .
							' AND a.access <= ' .(int) $user->get('aid', 0) .
							' AND ( CONCAT(",", REPLACE(a.metakey,", ",","),",") LIKE "%'.implode('%" OR CONCAT(",", REPLACE(a.metakey,", ",","),",") LIKE "%', $likes).'%" )' . //remove single space after commas in keywords
							' AND ( a.publish_up = '.$db->Quote($nullDate).' OR a.publish_up <= '.$db->Quote($now).' )' .
							' AND ( a.publish_down = '.$db->Quote($nullDate).' OR a.publish_down >= '.$db->Quote($now).' )';
					$db->setQuery($query);
					$temp = $db->loadObjectList();

					if (count($temp))
					{
						foreach ($temp as $row)
						{
							if (($row->cat_state == 1 || $row->cat_state == '') && ($row->sec_state == 1 || $row->sec_state == '') && ($row->cat_access <= $user->get('aid', 0) || $row->cat_access == '') && ($row->sec_access <= $user->get('aid', 0) || $row->sec_access == ''))
							{
								$row->route = JRoute::_(ContentHelperRoute::getArticleRoute($row->slug, $row->catslug, $row->sectionid));
								$related[] = $row;
							}
						}
					}
					unset ($temp);
				}
			}
		}

		return $related;
	}
}
