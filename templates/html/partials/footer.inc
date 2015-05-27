<footer>
	<p>
		<?php
			global $startTime;

			# Calculate the process time
			$endTime = microtime(1);
			$processTime = $endTime - $startTime;
			echo "<!-- Process Time: $processTime -->";
		?>
	</p>
</footer>
<?php
	$this->addToAsset('scripts', 'https://maps.googleapis.com/maps/api/js?sensor=false');
	$this->addToAsset('scripts', BASE_URI.'/js/MyCity.js');
	
	if (isset($this->assets['scripts'])) {
		foreach ($this->assets['scripts'] as $url) {
			echo "<script type=\"text/javascript\" src=\"$url\"></script>\n";
		}
	}
	if (isset($this->assets['stylesheets'])) {
		foreach ($this->assets['stylesheets'] as $url) {
			echo "<link rel=\"stylesheet\" href=\"$url\" />\n";
		}
	}
?>
