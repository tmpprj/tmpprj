<?php 
defined('JPATH_BASE') or die();
?>
<fieldset class="adminform">
	<legend><?php echo JText::_( 'Metadata Settings' ); ?></legend>
	<table class="admintable" cellspacing="1">

		<tbody>
		<tr>
			<td width="185" valign="top" class="key">
				<?php echo JText::_( 'Global Site Meta Description' ); ?>
			</td>
			<td>
				<textarea class="text_area" cols="50" rows="3" style="width:400px; height:50px" name="MetaDesc"><?php echo $row->MetaDesc; ?></textarea>
			</td>
		</tr>
		<td valign="top" class="key">
				<span class="editlinktip hasTip" title="<?php echo JText::_( 'Meta tag description settings' ); ?>::<?php echo JText::_( 'TIPMETATAGDESCRIPTIONSETTINGS' ); ?>">
					<?php echo JText::_( 'META tag description settings' ); ?>
				</span>
			</td>
			<td>
				<?php echo $lists['description']; ?>
			</td>
		</tr>
		<tr>
			<td colspan="2">
			</td>
		</tr>
		<tr>
			<td valign="top" class="key">
				<?php echo JText::_( 'Global Site Meta Keywords' ); ?>
			</td>
			<td>
				<textarea class="text_area" cols="50" rows="3" style="width:400px; height:50px" name="MetaKeys"><?php echo $row->MetaKeys; ?></textarea>
			</td>
		</tr>
		<tr>
			<td valign="top" class="key">
				<span class="editlinktip hasTip" title="<?php echo JText::_( 'Meta tag keywords settings' ); ?>::<?php echo JText::_( 'TIPMETATAGKEYWORDSSETTINGS' ); ?>">
					<?php echo JText::_( 'META tag keywords settings' ); ?>
				</span>
			</td>
			<td>
				<?php echo $lists['keywords']; ?>
			</td>
		</tr>

		<tr>
			<td valign="top" class="key">
				<?php echo JText::_( 'Generator tag' ); ?>
			</td>
			<td>
				<input class="text_area" type="text" size="70" name="generator_tag" value="<?php echo $row->generator_tag; ?>" />
			</td>
		</tr>
		<tr>
			<td valign="top" class="key">
				<span class="editlinktip hasTip" title="<?php echo JText::_( 'Custom fields default setting' ); ?>::<?php echo JText::_( 'TIPCUSTOMDEFAULTSETTING' ); ?>">
					<?php echo JText::_( 'Custom fields default setting' ); ?>
				</span>
			</td>
			<td>
				<?php echo $lists['Metacustomfields']; ?>
			</td>
		</tr>
		</tbody>
	</table>
</fieldset>
