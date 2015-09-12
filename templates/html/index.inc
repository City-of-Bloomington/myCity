<!doctype html>
<html lang="en">
<?php
	$this->layout = 'index';
	$this->_include('partials/header.inc');
?>
<body>
	<?php
		$this->_include('partials/pageHeader.inc');
	?>
    <main class="myCity-home">
		<div class="myCity-home-mapCanvas" id="map-canvas" data-latitude="<?= DEFAULT_LATITUDE - .055 ?>" data-longitude="<?= DEFAULT_LONGITUDE ?>"></div>
			<?php
				include BLOSSOM.'/errorMessages.php';

				echo $this->includeBlocks();
			?>
    </main>
	<?php
		$this-> _include('partials/footer.inc');
	?>
</body>
</html>
<?php
	$this->_include('partials/garbageCollection.inc');
?>
