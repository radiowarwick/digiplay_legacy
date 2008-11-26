<html>
    <head>
        <title>Add Script</title>
        <link rel="stylesheet" type="text/css" href="DPS/stylesheet.css" />
    </head>
    <body>
        {if $VIEWER.error != ''}
            {$VIEWER.error}
        {else}
        <div class='alignleft'>
    	    <div class='bigTitle'>Select a Script</div>
			<div class='subTitle'>Showplan: {$VIEWER.show.name}, Item: {$VIEWER.item.position}</div>
    	    <hr>
		    {if $VIEWER.write == 't'}
    	        <div class=''>
      	            <form name="dpsUserScriptShow" method="post" action="{$CONFIG.general.siteRoot}">
      		            <input type="hidden" name="formName" value="dpsUserScriptShow" />
      		            <input type="hidden" name="moduleName" value="DPS" />
      		            <input type="hidden" name="templateID" value="22" />
      		            <input type="hidden" name="itemID" value="{$VIEWER.item.id}" />
                        <ul>
                        {foreach from=$VIEWER.scripts item=script}
                            <li>{templateLink id="22" text=$script.text
                                _formName="dpsUserScriptShow" _moduleName="DPS"
                                _itemID=$VIEWER.item.id
                                _scriptID=$script.id}</li>
                        {/foreach}
                        </ul>
      	            </form>
    	        </div>
			    <hr>
            {else}
		        <b>{$VIEWER.item.scriptTitle}</b>
		    {/if}
        {/if}
    </body>
</html>
