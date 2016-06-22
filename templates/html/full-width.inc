<!DOCTYPE html>
<html lang="en">
<?php
	$this->layout = 'full-width';
	$this->_include('partials/head.inc');
?>
<body class="fn1 widthConstrained">
	<?php
		$this->_include('partials/pageHeader.inc');
	?>
	<main class="main">
		<div class="main-container" id="content-panel">
			<?php
				include BLOSSOM.'/errorMessages.php';

				echo $this->includeBlocks();
			?>
		</div>
	</main>
	<?php
		$this-> _include('partials/footer.inc');
	?>
</body>
</html>
<?php
	$this->_include('partials/garbageCollection.inc');
?>
