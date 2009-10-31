<?php 
defined('JPATH_BASE') or die();
?>
<fieldset class="adminform">
	<legend><?php echo JText::_( 'Metafields Settings' ); ?></legend>
	<table class="admintable" cellspacing="1">

		<tbody>
		<tr>
			<td valign="top" class="key">
				<span class="editlinktip hasTip" title="<?php echo JText::_( 'HTML Title setting' ); ?>::<?php echo JText::_( 'TIPHTMLTITLESETTING' ); ?>">
					<?php echo JText::_( 'HTML Title setting' ); ?>
				</span>
			</td>
			<td>
				<input class="text_area" type="text" size="50" name="html_title_config" value="<?php echo $row->html_title_config; ?>" />
			</td>
		</tr>
		<tr>
			<td valign="top" class="key">
				<span class="editlinktip hasTip" title="<?php echo JText::_( 'Default title' ); ?>::<?php echo JText::_( 'TIPDEFAULTTITLESETTING' ); ?>">
					<?php echo JText::_( 'Default title' ); ?>
				</span>
			</td>
			<td>
				<input class="text_area" type="text" size="50" name="html_title_default" value="<?php echo $row->html_title_default; ?>" />
			</td>
		</tr>
		<tr>
			<td valign="top" class="key">
				<span class="editlinktip hasTip" title="<?php echo JText::_( 'Meta tag robots settings' ); ?>::<?php echo JText::_( 'TIPMETATAGROBOTSSSETTINGS' ); ?>">
					<?php echo JText::_( 'Meta tag robots settings' ); ?>
				</span>
			</td>
			<td>
				<?php echo $lists['robots']; ?>
			</td>
		</tr>
		<tr>
			<td valign="top" class="key">
				<span class="editlinktip hasTip" title="<?php echo JText::_( 'Show Title Meta Tag' ); ?>::<?php echo JText::_( 'TIPSHOWTITLEMETATAGITEMS' ); ?>">
					<?php echo JText::_( 'Show Title Meta Tag' ); ?>
				</span>
			</td>
			<td>
				<?php echo $lists['MetaTitle']; ?>
			</td>
		</tr>
		<tr>
			<td valign="top" class="key">
				<span class="editlinktip hasTip" title="<?php echo JText::_( 'Show Author Meta Tag' ); ?>::<?php echo JText::_( 'TIPSHOWAUTHORMETATAGITEMS' ); ?>">
					<?php echo JText::_( 'Show Author Meta Tag' ); ?>
				</span>
			</td>
			<td>
				<?php echo $lists['MetaAuthor']; ?>
			</td>
		</tr>
		<tr>
			<td valign="top" class="key">
				<span class="editlinktip hasTip" title="<?php echo JText::_( 'Show joomla generator tag' ); ?>::<?php echo JText::_( 'TIPJOOMLAGENERATORTAG' ); ?>">
					<?php echo JText::_( 'Show joomla generator tag' ); ?>
				</span>
			</td>
			<td>
				<?php echo $lists['generator']; ?>
			</td>
		</tr>
		
		</tbody>
	</table>
</fieldset>
