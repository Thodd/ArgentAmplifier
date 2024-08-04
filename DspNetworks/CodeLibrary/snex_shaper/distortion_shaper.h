template <int NumVoices> struct distortion_shaper
{
	SNEX_NODE(distortion_shaper);
	
	// Implement the Waveshaper here...
	float factor = 0.0f;
	
	float getSample(float input)
	{
		float A = 0.5f;

		if (input > 0.0f) {
			return Math.tanh(factor * input);
		} else if (input <= 0.0f) {
			return Math.tanh(A * factor * input);
		}

		//return factor * input / (1.0f + Math.abs(factor * input));
	}
	// These functions are the glue code that call the function above
	template <typename T> void process(T& data)
	{
		for(auto ch: data)
		{
			for(auto& s: data.toChannelData(ch))
			{
				s = getSample(s);
			}
		}
	}
	template <typename T> void processFrame(T& data)
	{
		for(auto& s: data)
			s = getSample(s);
	}
	void reset()
	{
		
	}
	void prepare(PrepareSpecs ps)
	{
		
	}
	
	void setExternalData(const ExternalData& d, int index)
	{
	}
	template <int P> void setParameter(double v)
	{
		factor = v;
	}
};
